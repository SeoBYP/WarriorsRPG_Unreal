// Vince Petrelli All Rights Reserved

#include "Components/Interaction/InteractorComponent.h"
#include "WarriorDebugHelper.h"
#include "Components/Interaction/InteractableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// 상호작용자 컴포넌트 생성자
UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // 매 프레임마다 틱 업데이트 가능하게 설정
	SetIsReplicatedByDefault(false); // 기본적으로 네트워크 복제를 비활성화
}

// 컴포넌트가 플레이 상태로 진입할 때 호출되는 함수
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 상호작용 감지를 활성화/비활성화하는 타이머를 설정 (감지가 활성화된 상태로 시작)
	FTimerDelegate ToggleDetectionDelegate = FTimerDelegate::CreateUObject(
		this, &ThisClass::SetDetectionActive, bStartWithInteractionActive);
	GetWorld()->GetTimerManager().SetTimerForNextTick(ToggleDetectionDelegate); // 다음 틱에서 타이머 실행
}

// 매 프레임마다 호출되는 함수
void UInteractorComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bDetectionActive) // 감지가 비활성화된 경우 업데이트 중지
		return;

	UpdateDetection(DeltaTime); // 감지 업데이트
	UpdateInteraction(DeltaTime); // 상호작용 업데이트
}

// 네트워크에서 복제할 프로퍼티 정의
void UInteractorComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// 상호작용 감지를 활성화/비활성화하는 함수
void UInteractorComponent::SetDetectionActive(const bool bNewActive)
{
	APawn* Pawn = Cast<APawn>(GetOwner()); // 소유자가 Pawn인지 확인
	if (!IsValid(Pawn) || !Pawn->IsLocallyControlled()) // 유효하지 않거나 제어되지 않는 경우
	{
		Debug::Log(TEXT("제어되지 않는 캐릭터에서 상호작용을 토글하려고 시도했는데, 이로 인해 충돌이 발생할 수 있습니다. 참고: 플레이어 캐릭터가 아닌 청사진에 상호작용 컴포넌트를 추가해서는 안 됩니다."));
		bDetectionActive = false;
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	if (!IsValid(PlayerController)) // 플레이어 컨트롤러가 유효하지 않으면 비활성화
	{
		Debug::Log(TEXT("제어되지 않는 캐릭터에서 상호작용을 토글하려고 시도했는데, 이로 인해 충돌이 발생할 수 있습니다. 참고: 플레이어 캐릭터가 아닌 청사진에 상호작용 컴포넌트를 추가해서는 안 됩니다."));
		bDetectionActive = false;
		return;
	}

	bDetectionActive = bNewActive; // 새로운 활성 상태로 설정

	// 감지가 비활성화된 경우 오버랩 상태를 초기화
	if (!bDetectionActive)
	{
		for (auto Temp : OverlappingInteractables)
		{
			Temp->UpdateOverlap(false, this); // 오버랩 상태 업데이트
			if (Temp == HoveringInteractable)
			{
				Temp->UpdateHover(false, this); // 호버 상태 업데이트
				Temp->SetCurrentInteractionTime(0, this); // 상호작용 시간 초기화
				HoveringInteractable = nullptr; // 호버 상태 초기화
			}
		}
		OverlappingInteractables.Empty(); // 오버랩 중인 상호작용 배열 초기화
	}
}

// 상호작용 감지를 업데이트하는 함수
void UInteractorComponent::UpdateDetection(float DeltaTime)
{
	TimeSinceLastUpdate += DeltaTime; // 마지막 업데이트 이후의 시간 추가
	if (TimeSinceLastUpdate >= DetectionFrequency) // 설정된 감지 주기에 도달했을 때 업데이트
	{
		TimeSinceLastUpdate = 0.f;
		UpdateOverlappingInteractables(); // 오버랩된 상호작용 컴포넌트 업데이트
		UpdateHoveringInteractables(); // 호버 상태의 상호작용 컴포넌트 업데이트
	}
}

// 감지를 위한 트레이스(충돌 검사) 수행
TArray<UActorComponent*> UInteractorComponent::DetectionTrace()
{
	FVector Location = GetOwner()->GetActorLocation(); // 소유자의 현재 위치
	ETraceTypeQuery DetectionTraceQuery = UEngineTypes::ConvertToTraceType(DetectionChannel); // 감지할 트레이스 채널 설정
	TArray<UActorComponent*> DetectedComponents; // 감지된 컴포넌트 저장할 배열

	TArray<FHitResult> HitResults;
	// 구형 트레이스를 사용해 감지
	UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Location, Location, DetectionRadius, DetectionTraceQuery,
	                                       false, {GetOwner()}, GetDrawDebugType(), HitResults, true,
	                                       FLinearColor::Red, FLinearColor::Green, DetectionFrequency);

	for (const FHitResult& HitResult : HitResults)
	{
		if (AActor* HitActor = HitResult.GetActor()) // 감지된 액터가 유효한지 확인
		{
			TArray<UActorComponent*> TempComponents;
			HitActor->GetComponents(UInteractableComponent::StaticClass(), TempComponents, true); // 상호작용 가능한 컴포넌트를 가져옴
			DetectedComponents.Append(TempComponents); // 감지된 컴포넌트를 추가
		}
	}
	return DetectedComponents;
}

// 오버랩된 상호작용 컴포넌트를 업데이트하는 함수
void UInteractorComponent::UpdateOverlappingInteractables()
{
	// 트레이스를 통해 감지된 상호작용 컴포넌트들을 가져옴
	TArray<UActorComponent*> DetectedInteractables = DetectionTrace();

	// 감지된 컴포넌트들을 순회
	for (auto TempActorComponent : DetectedInteractables)
	{
		// 이미 오버랩 상태인 컴포넌트는 건너뜀
		if (OverlappingInteractables.Contains(TempActorComponent))
			continue;

		// 상호작용 컴포넌트인지 확인
		UInteractableComponent* TempInteractable = Cast<UInteractableComponent>(TempActorComponent);
		if (!IsValid(TempInteractable))
			continue;

		// 상호작용이 활성화된 경우 오버랩 목록에 추가
		if (TempInteractable->IsInteractionActive())
		{
			OverlappingInteractables.AddUnique(TempInteractable);
		}
	}

	// 이전에 감지된 상호작용 컴포넌트 중, 더 이상 유효하지 않거나 조건을 만족하지 않는 컴포넌트 제거
	OverlappingInteractables.RemoveAllSwap([this](UInteractableComponent* TempInteractable)
	{
		if (!IsValid(TempInteractable))
			return true; // 유효하지 않은 경우 제거

		const bool bIsBeingOverlapped = TempInteractable->GetIsBeingOverlapped();
		const bool bIsBeingHovered = TempInteractable->GetIsBeingHovered() && HoveringInteractable == TempInteractable;

		TempInteractable->ExecuteObstructionTrace(this); // 방해물 검사 수행
		const bool bIsObstructed = TempInteractable->GetIsObstructed();

		if (!TempInteractable->IsInteractionActive()) // 상호작용이 비활성화된 경우
		{
			if (bIsBeingOverlapped)
				TempInteractable->UpdateOverlap(false, this);

			if (bIsBeingHovered)
			{
				TempInteractable->UpdateHover(false, this);
				HoveringInteractable == nullptr;
			}
			return true; // 제거 대상
		}

		const float DistanceFromOrigin = FVector::Distance(GetOwner()->GetActorLocation(), TempInteractable->GetComponentLocation());
		const bool bInOverlapRange = DistanceFromOrigin <= TempInteractable->GetInteractableData().MaxOverlapDistance;

		// 유효 범위 내에 있으면 오버랩 상태로 전환
		if (bInOverlapRange && !bIsBeingOverlapped && !bIsObstructed)
		{
			TempInteractable->UpdateOverlap(true, this);
			return false; // 유지
		}
		else if ((!bInOverlapRange || bIsObstructed) && bIsBeingOverlapped)
		{
			TempInteractable->UpdateOverlap(false, this);
			if (bIsBeingHovered)
			{
				TempInteractable->UpdateHover(false, this);
				HoveringInteractable == nullptr;
			}
			return true; // 제거
		}
		return false; // 유지
	});
}

// 호버 상태의 상호작용 컴포넌트를 업데이트하는 함수
void UInteractorComponent::UpdateHoveringInteractables()
{
	UInteractableComponent* UpdatedInteractable = SelectHoveringInteractable(); // 호버할 상호작용 컴포넌트 선택

	if (UpdatedInteractable != HoveringInteractable) // 현재 호버 중인 컴포넌트와 다를 경우 업데이트
	{
		if (IsValid(HoveringInteractable)) // 기존 호버 상태 초기화
		{
			HoveringInteractable->UpdateHover(false, this);
			HoveringInteractable->SetCurrentInteractionTime(0.f, this);
		}

		HoveringInteractable = UpdatedInteractable;
		
		if (IsValid(HoveringInteractable)) // 새롭게 호버 상태로 전환
		{
			HoveringInteractable->UpdateHover(true, this);
			HoveringInteractable->SetCurrentInteractionTime(0.f, this);
		}
	}
}

// 현재 호버 상태의 상호작용 컴포넌트를 선택하는 함수
UInteractableComponent* UInteractorComponent::SelectHoveringInteractable()
{
	if (OverlappingInteractables.IsEmpty()) // 오버랩된 상호작용 컴포넌트가 없으면 nullptr 반환
		return nullptr;

	UInteractableComponent* TempHoveringComponent {};
	float TargetDistanceFromOrigin = DetectionRadius;
	const FVector CharacterLocation = GetOwner()->GetActorLocation();
	const FVector CharacterDirection = GetOwner()->GetActorRotation().Vector();

	// 화면 크기 가져오기
	FVector2d ScreenSize;
	GEngine->GameViewport->GetViewportSize(ScreenSize);
	const FVector2d ScreenCenter = ScreenSize/2;
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	for (auto Temp : OverlappingInteractables)
	{
		if (!Temp->GetInteractableData().bAllowInteractionWhenObstructed && Temp->GetIsObstructed())// 방해물이 있을 경우 무시
			continue;

		const float DistanceFromCharacter = FVector3d::Distance(CharacterLocation, Temp->GetComponentLocation());;
		float DistanceFromOrigin = DistanceFromCharacter;

		const bool bInHoverRangeCharacterRelative = DistanceFromCharacter <= Temp->GetInteractableData().MaxHoverDistanceFromCharacter;
		bool bInHoverRangeCameraRelative = true;

		if (DetectionMode == EDetectionMode::DM_CameraProximity)
		{
			const bool bInFrontOfCharacter = FVector::DotProduct(CharacterDirection, (Temp->GetComponentLocation() - CharacterLocation).GetSafeNormal()) > 0;
			if (!bInFrontOfCharacter)
				continue;
			
			FVector2d ScreenPosition;
			UGameplayStatics::ProjectWorldToScreen(PlayerController, Temp->GetComponentLocation(), ScreenPosition);

			DistanceFromOrigin = FVector2D::Distance(ScreenCenter, ScreenPosition);
			bInHoverRangeCameraRelative = DistanceFromOrigin <= Temp->GetInteractableData().MaxHoverDistanceFromCharacter;
		}
		
		if (bInHoverRangeCharacterRelative && bInHoverRangeCameraRelative && DistanceFromOrigin <= TargetDistanceFromOrigin)
		{
			TargetDistanceFromOrigin = DistanceFromOrigin;
			TempHoveringComponent = Temp;	
		}
	}
	return TempHoveringComponent;
}

// 상호작용 입력을 처리하는 함수
void UInteractorComponent::InteractionInput(FString Key, bool bPressed)
{
	if (bPressed) // 입력이 눌렸을 때
	{
		ActiveKey.AddUnique(Key); // 입력 키 추가
		if (!IsValid(HoveringInteractable))
			return;

		if (!HoveringInteractable->GetInteractableData().Keys.Contains(Key))
			return;

		if (HoveringInteractable->GetInteractableData().InteractionType == EInteractionType::EIT_Hold)
			return;

		HoveringInteractable->SetCurrentInteractionTime(HoveringInteractable->GetInteractionTime(), this); // 상호작용 시간 설정
		Interact(HoveringInteractable); // 상호작용 실행
	}
	else // 입력이 해제되었을 때
	{
		ActiveKey.Remove(Key); // 입력 키 제거
		if (!IsValid(HoveringInteractable))
			return;

		if (!HoveringInteractable->GetInteractableData().Keys.Contains(Key))
			return;

		HoveringInteractable->SetCurrentInteractionTime(0.f, this); // 상호작용 시간 초기화
	}
}

// 상호작용을 업데이트하는 함수
void UInteractorComponent::UpdateInteraction(float DeltaTime)
{
	if (ActiveKey.IsEmpty()) // 활성 키가 없으면 종료
		return;
	if (!IsValid(HoveringInteractable))
		return;

	for (auto Key : ActiveKey)
	{
		if (!HoveringInteractable->GetInteractableData().Keys.Contains(Key))
			continue;

		if (HoveringInteractable->GetInteractableData().InteractionType == EInteractionType::EIT_Press)
			continue;

		const float Progress = HoveringInteractable->SetCurrentInteractionTime(HoveringInteractable->GetInteractionTime() + DeltaTime, this);

		if (Progress >= 1.0f) // 상호작용이 완료되었을 때
		{
			Interact(HoveringInteractable); // 상호작용 실행
		}
	}
}

// 감지 모드를 설정하는 함수
void UInteractorComponent::SetDetectionMode(EDetectionMode NewDetectionMode)
{
	if (DetectionMode == NewDetectionMode) // 동일한 모드로 변경할 필요 없음
		return;

	DetectionMode = NewDetectionMode;
	OnDetectionModeChanged.Broadcast(DetectionMode); // 감지 모드 변경 브로드캐스트
}

// 상호작용을 실행하는 함수
void UInteractorComponent::Interact(UInteractableComponent* Interactable)
{
	const FVector CharacterLocation = GetOwner()->GetActorLocation();
	const float DistanceFromCharacter = FVector3d::Distance(CharacterLocation, Interactable->GetComponentLocation());
	const bool bIsObstructed = Interactable->ExecuteObstructionTrace(this) && !Interactable->GetInteractableData().bAllowInteractionWhenObstructed;

	if (bIsObstructed) // 방해물이 있을 경우 상호작용 중지
		return;

	if (DistanceFromCharacter > Interactable->GetInteractableData().MaxHoverDistanceFromCharacter) // 거리 초과 시 상호작용 중지
		return;

	if (!Interactable->IsInteractionActive()) // 상호작용이 비활성화된 경우 중지
		return;

	Interactable->SetCurrentInteractionTime(0.f, this); // 상호작용 시간 초기화
	Interactable->Interact(this); // 상호작용 실행
	OnInteract.Broadcast(Interactable); // 상호작용 브로드캐스트
}
