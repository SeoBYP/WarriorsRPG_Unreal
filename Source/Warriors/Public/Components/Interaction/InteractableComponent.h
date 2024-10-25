// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "DataTables/InteractableDataTable.h"
#include "InteractableComponent.generated.h"

class UInteractorComponent;

// 위젯 정보를 업데이트하는 델리게이트, 상호작용 가능한 컴포넌트를 파라미터로 전달
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateWidgetInfo, UInteractableComponent*, InteractableComponent);

// 오버랩 상태가 업데이트될 때 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnOverlapUpdated, bool, bIsOverlaping, UInteractorComponent*, OverlappingInteractor, UInteractableComponent*, Interactable);

// 호버 상태가 업데이트될 때 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHoverUpdated, bool, bIsHovering, UInteractorComponent*, HoveringInteractor, UInteractableComponent*, Interactable);

// 상호작용 입력 상태가 토글될 때 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnInteractionInputToggled, bool, bIsInputPressed, UInteractorComponent*, HoveringInteractor, UInteractableComponent*, Interactable);

// 상호작용 진행 백분율이 변경될 때 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionPercentageChanged, float, Percentage, UInteractableComponent*, Interactable);

// 상호작용이 발생할 때 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteract, UInteractorComponent*, Interactor, UInteractableComponent*, Interactable);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), AutoExpandCategories = ("Behaviour"))
class WARRIORS_API UInteractableComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// 생성자, 기본 설정을 초기화
	UInteractableComponent();
	
	// 게임이 시작되면 호출되는 함수
	virtual void BeginPlay() override;

	// 컴포넌트가 네트워크에서 복제될 때 어떤 데이터를 복제할지 설정
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	// 매 프레임마다 호출되는 함수, DeltaTime과 현재 틱 상태를 인자로 받음
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// 상호작용이 활성화된 상태로 시작할지 여부를 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Behavior", meta = (AllowPrivateAccess = true))
	bool bStartWithInteractionActive = true;

	// 상호작용 데이터 테이블을 복제하여 사용, ReplicatedUsing은 OnReplicated_InteractableData 함수로 복제될 때 호출됨
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnReplicated_InteractableData", Category = "Behavior")
	FInteractableDataTable InteractableData{};

	// 방해물 탐지 시 무시할 액터 목록을 저장
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Behavior")
	TArray<TObjectPtr<AActor>> ActorsToIgnoreOnObstructionTrace;

private:
	// 현재 상호작용 시간이 저장됨
	float CurrentInteractionTime = 0.f;
	// 상호작용 후 경과 시간
	float TimeSinceInteraction = 0.5f;

	// 상호작용이 활성화되어 있는지 여부, 복제 시 OnReplicated_bInteractionActive 함수 호출
	UPROPERTY(ReplicatedUsing = "OnReplicated_bInteractionActive")
	bool bInteractionActive = true;

	// 오버랩 상태인지 여부를 저장
	bool bIsBeingOverlapped = false;
	// 호버 상태인지 여부를 저장
	bool bIsBeingHovered = false;
	// 방해물이 있는지 여부를 저장
	bool bIsObstructed = false;

public:
	// 위젯 정보 업데이트 시 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnUpdateWidgetInfo OnUpdateWidgetInfo;

	// 오버랩 상태가 업데이트될 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnOverlapUpdated OnOverlapUpdated;

	// 호버 상태가 업데이트될 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnHoverUpdated OnHoverUpdated;

	// 상호작용 입력 상태가 토글될 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnInteractionInputToggled OnInteractionInputToggled;

	// 상호작용 백분율이 변경될 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnInteractionPercentageChanged OnInteractionPercentageChanged;

	// 상호작용이 발생할 때 호출되는 델리게이트
	UPROPERTY(BlueprintAssignable, Category = "Behavior")
	FOnInteract OnInteract;

protected:
	// 상호작용 데이터를 갱신하는 함수
	void RefreshInteractableData();

	// 위젯 참조를 초기화하는 함수
	void InitializeWidgetReferences();

	// 상호작용 데이터가 복제될 때 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void OnReplicated_InteractableData();
	
public:
	// 오버랩 상태를 업데이트하는 함수
	UFUNCTION(BlueprintCallable)
	void UpdateOverlap(const bool bIsOverlapping, UInteractorComponent* OverlappingInteractorComponent);

	// 호버 상태를 업데이트하는 함수
	UFUNCTION(BlueprintCallable)
	void UpdateHover(const bool bIsHovering, UInteractorComponent* HoveringInteractorComponent);

	// 상호작용을 수행하는 함수
	UFUNCTION(BlueprintCallable)
	void Interact(UInteractorComponent* Interactor);
	
	// 상호작용 활성화 상태가 복제될 때 호출되는 함수
	UFUNCTION(BlueprintCallable)
	void OnReplicated_bInteractionActive();
	
	// 방해물 탐지를 수행하는 함수
	UFUNCTION(BlueprintCallable)
	bool ExecuteObstructionTrace(UInteractorComponent* Interactor);

public:
	// 상호작용 데이터를 반환하는 함수
	UFUNCTION(BlueprintCallable, Category = "Data")
	FORCEINLINE FInteractableDataTable GetInteractableData() const { return InteractableData; }

	// 상호작용이 활성화된 상태인지 반환하는 함수
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FORCEINLINE bool IsInteractionActive() const { return bInteractionActive; }

	// 오버랩 상태인지 반환하는 함수
	UFUNCTION(BlueprintPure, Category = "Detection")
	FORCEINLINE bool GetIsBeingOverlapped() const { return bIsBeingOverlapped; }

	// 호버 상태인지 반환하는 함수
	UFUNCTION(BlueprintPure, Category = "Detection")
	FORCEINLINE bool GetIsBeingHovered() const { return bIsBeingHovered; }

	// 방해물이 있는지 반환하는 함수
	UFUNCTION()
	FORCEINLINE bool GetIsObstructed() const { return bIsObstructed; }

	// 상호작용 시간을 반환하는 함수
	UFUNCTION()
	FORCEINLINE float GetInteractionTime() const { return CurrentInteractionTime; }

public:
	// 상호작용 시간을 설정하는 함수
	UFUNCTION(BlueprintCallable)
	float SetCurrentInteractionTime(const float NewInteractionTime, UInteractorComponent* Interactor);

	// 상호작용을 활성화 또는 비활성화하는 함수
	UFUNCTION(BlueprintCallable)
	void SetInteractionActive(bool bNewActive);

public:
	// 데이터 테이블을 기반으로 상호작용 데이터를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Data")
	void SetInteractableDataBasedOnDataTable(UDataTable* DataTable, FName RowName);

	// 표시할 텍스트를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Data")
	void SetDisplayText(const FString NewText = "Placeholder Text");

	// 툴팁 텍스트를 설정하는 함수
	UFUNCTION(BlueprintCallable, Category = "Data")
	void SetTooltipText(const FString NewText = "Placeholder Text");
};
