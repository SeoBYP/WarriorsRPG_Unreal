// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InteractorComponent.generated.h"

class UInteractableComponent;

// 상호작용 감지 모드를 정의하는 열거형 (카메라 기준 또는 캐릭터 기준)
UENUM(BlueprintType)
enum class EDetectionMode : uint8
{
	DM_CameraProximity UMETA(DisplayName="Camera Proximity"),  // 카메라 근접 기준
	DM_CharacterProximity UMETA(DisplayName="Character Proximity")  // 캐릭터 근접 기준
};

// 플레이어 상호작용 델리게이트 (상호작용 가능한 컴포넌트를 파라미터로 전달)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInteract, UInteractableComponent*, Interactable);
// 감지 모드 변경 시 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectionModeChanged, EDetectionMode, NewDetectionMode);

// 상호작용자 컴포넌트 클래스
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 생성자: 기본 설정 초기화
	UInteractorComponent();

	// 매 프레임마다 호출되는 함수 (DeltaTime: 경과 시간, TickType: 틱 상태, ThisTickFunction: 틱 함수 포인터)
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// 네트워크에서 복제할 프로퍼티 정의
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// 게임 시작 시 호출되는 함수
	virtual void BeginPlay() override;

private:
	// 상호작용 감지 모드 (기본값은 카메라 기준)
	UPROPERTY(EditDefaultsOnly, Category="Detection")
	EDetectionMode DetectionMode = EDetectionMode::DM_CameraProximity;
	
	// 감지 관련 변수
protected:
	// 감지할 트레이스 채널 (기본값은 카메라 채널)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Detection", meta=(AllowPrivateAccess=true))
	TEnumAsByte<ECollisionChannel> DetectionChannel = ECC_Camera;

	// 감지 주기 (초 단위, 기본값은 0.1초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection", meta=(AllowPrivateAccess=true))
	float DetectionFrequency = 0.1f;

	// 감지 반경 (기본값은 700 유닛)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection", meta=(AllowPrivateAccess=true))
	float DetectionRadius = 700.f;
	
protected:
	// 상호작용이 기본적으로 활성화되어 시작할지 여부 (기본값: 활성화)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Detection", meta=(AllowPrivateAccess=true))
	bool bStartWithInteractionActive = true;

	// 내부적으로 사용되는 변수
	bool bDetectionActive = false;  // 감지가 활성화되었는지 여부
	float TimeSinceLastUpdate = 0.f;  // 마지막 업데이트 이후 경과 시간

	// 오버랩된 상호작용 가능한 컴포넌트 배열
	UPROPERTY(BlueprintReadOnly, Category="Detection", meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<UInteractableComponent>> OverlappingInteractables;

	// 현재 호버 중인 상호작용 가능한 컴포넌트 참조
	UPROPERTY(BlueprintReadOnly, Category="Detection", meta=(AllowPrivateAccess=true))
	TObjectPtr<UInteractableComponent> HoveringInteractable;

private:
	// 현재 활성화된 입력 키 배열
	UPROPERTY(BlueprintReadOnly, Category="Interaction", meta=(AllowPrivateAccess=true))
	TArray<FString> ActiveKey = {};

public:
	// 감지 모드가 변경될 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category="Detection")
	FOnDetectionModeChanged OnDetectionModeChanged;

	// 상호작용이 발생할 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnPlayerInteract OnInteract;

protected:
	// 디버그 트레이스를 표시할지 여부 (기본값: true)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug", meta=(AllowPrivateAccess=true))
	bool bShowDebugTraces = true;

public:
	// 상호작용 감지를 활성화/비활성화하는 함수
	UFUNCTION(BlueprintCallable, Category = "Detection")
	void SetDetectionActive(const bool bNewActive);
	
private:
	// 감지 업데이트 함수
	UFUNCTION(BlueprintCallable)
	void UpdateDetection(float DeltaTime);

	// 감지를 위한 트레이스를 수행하는 함수 (감지된 컴포넌트 배열을 반환)
	UFUNCTION(BlueprintCallable)
	TArray<UActorComponent*> DetectionTrace();

	// 오버랩된 상호작용 가능한 컴포넌트를 업데이트하는 함수
	UFUNCTION(BlueprintCallable)
	void UpdateOverlappingInteractables();

	// 호버 중인 상호작용 가능한 컴포넌트를 업데이트하는 함수
	UFUNCTION(BlueprintCallable)
	void UpdateHoveringInteractables();

	// 호버 중인 상호작용 가능한 컴포넌트를 선택하는 함수
	UFUNCTION(BlueprintCallable)
	UInteractableComponent* SelectHoveringInteractable();

public:
	// 상호작용 입력 처리 함수 (키를 눌렀을 때와 해제했을 때의 상태를 처리)
	UFUNCTION(BlueprintCallable, Category="Input")
	void InteractionInput(FString Key = "DefaultKey", bool bPressed = false);

private:
	// 상호작용을 업데이트하는 함수
	UFUNCTION()
	void UpdateInteraction(float DeltaTime);

	// 상호작용을 실행하는 함수
	UFUNCTION()
	void Interact(UInteractableComponent* Interactable);

public:
	// 감지 모드를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category="Detection")
	void SetDetectionMode(EDetectionMode NewDetectionMode);

public:
	// 디버그 트레이스를 설정하는 함수
	FORCEINLINE EDrawDebugTrace::Type GetDrawDebugType() const
	{
		return bShowDebugTraces ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None;
	}

	// 감지 주기를 반환하는 함수
	FORCEINLINE float GetDetectionFrequency() const { return DetectionFrequency; }

	// 현재 감지 모드를 반환하는 함수
	FORCEINLINE EDetectionMode GetDetectionMode() const { return DetectionMode; }

	// 오버랩된 상호작용 가능한 컴포넌트를 반환하는 함수
	UFUNCTION(BlueprintCallable, Category="Detection")
	TArray<UInteractableComponent*> GetOverlappingInteractables() const { return OverlappingInteractables; }

	// 호버 중인 상호작용 가능한 컴포넌트를 반환하는 함수
	UFUNCTION(BlueprintCallable, Category="Detection")
	UInteractableComponent* GetHoveringInteractable() const { return HoveringInteractable; }
};
