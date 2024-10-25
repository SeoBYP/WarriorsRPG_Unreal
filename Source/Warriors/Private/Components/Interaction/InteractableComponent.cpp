// Vince Petrelli All Rights Reserved

#include "Components/Interaction/InteractableComponent.h"
#include "WarriorDebugHelper.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/Interaction/InteractorComponent.h"
#include "Interfaces/InteractionInterface.h"

UInteractableComponent::UInteractableComponent()
{
	// 기본적으로 컴포넌트가 복제되지 않도록 설정하여 BP(블루프린트)에서 혼동을 방지
	SetIsReplicatedByDefault(false);

	// 위젯을 화면 공간에 표시하고 원하는 크기로 그리도록 설정
	SetWidgetSpace(EWidgetSpace::Screen);
	SetDrawAtDesiredSize(true);
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay(); // 부모 클래스의 BeginPlay 호출

	// Obstruction Trace(방해물 탐지)에서 자기 자신을 무시하도록 설정 (충돌 검사 시 자기 자신을 제외)
	ActorsToIgnoreOnObstructionTrace.Add(GetOwner());

	// 위젯 참조를 초기화
	InitializeWidgetReferences();

	// 상호작용을 활성 또는 비활성화 상태로 설정
	SetInteractionActive(bStartWithInteractionActive);
}

void UInteractableComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInteractableComponent, InteractableData); // InteractableData를 복제
	DOREPLIFETIME(UInteractableComponent, bInteractionActive); // bInteractionActive를 복제
	DOREPLIFETIME(UInteractableComponent, ActorsToIgnoreOnObstructionTrace); // ActorsToIgnoreOnObstructionTrace를 복제
}

void UInteractableComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceInteraction += DeltaTime; // 상호작용 이후의 시간 갱신
}

void UInteractableComponent::RefreshInteractableData()
{
	InitializeWidgetReferences(); // 위젯 참조 초기화
	OnUpdateWidgetInfo.Broadcast(this); // 위젯 정보 갱신 브로드캐스트
}

void UInteractableComponent::InitializeWidgetReferences()
{
	// 위젯을 생성
	InitWidget();

	// 위젯이 유효한지 확인
	if (!IsValid(GetWidget()))
		return;

	// 위젯이 상호작용 인터페이스를 구현하는지 확인 후 참조 초기화
	if (GetWidget()->Implements<UInteractionInterface>())
	{
		IInteractionInterface::Execute_InitializeReference(GetWidget(), this);
	}

	// 상호작용이 활성화 상태인지에 따라 위젯의 가시성을 토글
	if (IsValid(GetWidget()))
		GetWidget()->SetVisibility(bInteractionActive ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void UInteractableComponent::UpdateOverlap(const bool bIsOverlapping,
                                           UInteractorComponent* OverlappingInteractorComponent)
{
	// 겹쳐진 pawn의 참조 가져오기
	APawn* OverlappingPawn = Cast<APawn>(OverlappingInteractorComponent->GetOwner());
	if (!IsValid(OverlappingPawn))
	{
		Debug::LogWarning(TEXT("겹쳐진 Pawn이 유효하지 않습니다."));
		return;
	}

	bIsBeingOverlapped = bIsOverlapping; // 겹쳐진 상태 갱신

	if (bIsBeingOverlapped)
		OnUpdateWidgetInfo.Broadcast(this); // 겹쳐진 상태에서 위젯 정보 갱신

	OnOverlapUpdated.Broadcast(bIsOverlapping, OverlappingInteractorComponent, this); // 겹침 상태 갱신 브로드캐스트
}

void UInteractableComponent::UpdateHover(const bool bIsHovering, UInteractorComponent* HoveringInteractorComponent)
{
	// hover 상태인 pawn의 참조 가져오기
	APawn* HoveringPawn = Cast<APawn>(HoveringInteractorComponent->GetOwner());
	if (!IsValid(HoveringPawn))
	{
		Debug::LogWarning(TEXT("Hover 중인 Pawn이 유효하지 않습니다."));
		return;
	}

	bIsBeingHovered = bIsHovering; // hover 상태 갱신

	if (bIsHovering)
		OnUpdateWidgetInfo.Broadcast(this); // hover 상태에서 위젯 정보 갱신

	OnHoverUpdated.Broadcast(bIsHovering, HoveringInteractorComponent, this); // hover 상태 갱신 브로드캐스트
}

void UInteractableComponent::OnReplicated_InteractableData()
{
	RefreshInteractableData(); // 복제된 상호작용 데이터 갱신
}

void UInteractableComponent::Interact(UInteractorComponent* Interactor)
{
	OnInteract.Broadcast(Interactor, this); // 상호작용 브로드캐스트
}

float UInteractableComponent::SetCurrentInteractionTime(const float NewInteractionTime, UInteractorComponent* Interactor)
{
	// 상호작용 간의 딜레이를 확인하여 상호작용 시간을 설정
	if (TimeSinceInteraction < GetInteractableData().DelayBetweenInteraction)
		return 0.0f;

	CurrentInteractionTime = NewInteractionTime; // 현재 상호작용 시간 갱신

	// 상호작용 시간에 따라 백분율 계산
	const FVector2d Range(0.0f, 1);
	const FVector2d Time(0, GetInteractableData().InteractionDuration);
	const float Percent = FMath::GetMappedRangeValueClamped(Time, Range, NewInteractionTime);
	
	// 상호작용이 완료된 경우 시간 초기화
	if (Percent >= 1.0f)
	{
		TimeSinceInteraction = 0.f;
		CurrentInteractionTime = 0.f;

		OnInteractionPercentageChanged.Broadcast(0.f, this); // 상호작용 백분율 변경 브로드캐스트
		return Percent;
	}

	OnInteractionPercentageChanged.Broadcast(Percent, this); // 상호작용 백분율 변경 브로드캐스트
	return Percent;
}

void UInteractableComponent::SetInteractionActive(bool bNewActive)
{
	// 서버 권한이 있는 경우에만 상호작용 활성화 상태를 설정
	// if (GetOwner()->GetLocalRole() < ROLE_Authority)
	// 	return;

	bInteractionActive = bNewActive; // 상호작용 활성화 상태 갱신
	OnReplicated_bInteractionActive(); // 상호작용 상태 복제
}

void UInteractableComponent::OnReplicated_bInteractionActive()
{
	// 상호작용이 비활성화되면 겹침 및 hover 상태도 false로 설정
	if (!bInteractionActive)
	{
		bIsBeingOverlapped = false;
		bIsBeingHovered = false;
	}

	// 위젯이 유효하면 가시성 토글
	if (IsValid(GetWidget()))
	{
		GetWidget()->SetVisibility(bInteractionActive ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
	}
}

bool UInteractableComponent::ExecuteObstructionTrace(UInteractorComponent* Interactor)
{
	// 방해물 감지와 상호작용 허용 여부를 확인
	if (InteractableData.bDetectWhenObstructed && InteractableData.bAllowInteractionWhenObstructed)
	{
		bIsObstructed = false;
		return false;
	}

	ensure(IsValid(Interactor)); // Interactor가 유효한지 확인

	APlayerController* Controller = Cast<APlayerController>(Interactor->GetOwner()->GetInstigatorController());
	if (!IsValid(Controller))
	{
		Debug::LogWarning(TEXT("방해물 트레이스를 실행하려 했으나 플레이어 컨트롤러가 유효하지 않습니다. 충돌이 발생할 수 있습니다."));
		return true;
	}

	// 트레이스 시작 지점과 방향을 설정
	FVector StartLocation;
	FRotator StartRotation;
	Controller->GetActorEyesViewPoint(StartLocation, StartRotation);

	const ETraceTypeQuery TraceTypeQuery = UEngineTypes::ConvertToTraceType(InteractableData.ObstructionTraceChannel);
	FHitResult ObstructionResult{};

	ActorsToIgnoreOnObstructionTrace.AddUnique(Interactor->GetOwner()); // 자기 자신을 트레이스에서 제외
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		StartLocation,
		GetComponentLocation(),
		TraceTypeQuery,
		false,
		ActorsToIgnoreOnObstructionTrace,
		Interactor->GetDrawDebugType(),
		ObstructionResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		Interactor->GetDetectionFrequency()
	);

	// 트레이스 결과를 통해 방해 여부 확인
	bIsObstructed = ObstructionResult.bBlockingHit;
	ActorsToIgnoreOnObstructionTrace.Remove(Interactor->GetOwner()); // 트레이스에서 제외했던 자신의 참조 제거

	return bIsObstructed;
}

void UInteractableComponent::SetInteractableDataBasedOnDataTable(UDataTable* DataTable, FName RowName)
{
	// 서버 권한이 있는 경우에만 데이터 테이블 기반으로 상호작용 데이터 설정
	// if (GetOwner()->GetLocalRole() < ROLE_Authority)
	// 	return;
	if (!IsValid(DataTable))
	{
		Debug::LogError(TEXT("상호작용 데이터를 변경하는 데 실패했습니다. 데이터 테이블 행이 유효하지 않습니다. 충돌이 발생할 수 있습니다."));
		return;
	}

	// 데이터 테이블에서 해당 행을 찾음
	FInteractableDataTable* TempData = DataTable->FindRow<FInteractableDataTable>(RowName, TEXT("해당 행을 찾을 수 없습니다."), false);
	if (!TempData)
	{
		Debug::LogError(TEXT("상호작용 데이터를 변경하는 데 실패했습니다. 데이터 테이블 행이 유효하지 않습니다. 충돌이 발생할 수 있습니다."));
		return;
	}
	InteractableData = *TempData; // 상호작용 데이터 설정
	OnUpdateWidgetInfo.Broadcast(this); // 위젯 정보 갱신
}

void UInteractableComponent::SetDisplayText(const FString NewText)
{
	// 서버 권한이 있는 경우에만 표시 텍스트를 설정
	// if (GetOwner()->GetLocalRole() < ROLE_Authority)
	// 	return;
	if (InteractableData.DisplayText.ToString() == NewText)
		return;

	InteractableData.DisplayText = FText::FromString(NewText); // 표시 텍스트 갱신
	OnReplicated_InteractableData(); // 복제된 데이터 갱신
}

void UInteractableComponent::SetTooltipText(const FString NewText)
{
	// 서버 권한이 있는 경우에만 툴팁 텍스트를 설정
	// if (GetOwner()->GetLocalRole() < ROLE_Authority)
	// 	return;
	if (InteractableData.TooltipText.ToString() == NewText)
		return;

	InteractableData.TooltipText = FText::FromString(NewText); // 툴팁 텍스트 갱신
	OnReplicated_InteractableData(); // 복제된 데이터 갱신
}
