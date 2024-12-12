// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "Widgets/Quest/QuestClearNotifyWidget.h"
#include "Widgets/Quest/QuestGiverWidget.h"
#include "Widgets/Quest/QuestRewardWidget.h"
#include "Widgets/Quest/QuestTrackerWidget.h"
#include "WidgetSubSystem.generated.h"

class UQuestLogWidget;
class UDialogueOverlayWidget;
class UInventoryWidget;
class UWarriorHeroHUD;
/**
 * 
 */

UENUM(BlueprintType)
enum class EWarriorWidgetType : uint8
{
	EWT_HUD = 1,
	EWT_Popup = 0,
	EWT_Overlay = 2,
};


UCLASS()
class WARRIORS_API UWidgetSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;  // 필요한 경우 레벨 전환 시 수행할 작업을 추가

protected:
	UPROPERTY(BlueprintReadOnly, Category = "HUD|HeroHUD",meta=(AllowPrivateAccess="true"))
	UWarriorHeroHUD* HUDWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory|InventoryWidget",meta=(AllowPrivateAccess="true"))
	UInventoryWidget* InventoryWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory|ContainerInventory",meta=(AllowPrivateAccess="true"))
	UContainerInventoryWidget* ContainerInventory;
	
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue|DialogueWidget",meta=(AllowPrivateAccess="true"))
	UDialogueOverlayWidget* DialogueWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Quest|QuestClearNotifyWidget",meta=(AllowPrivateAccess="true"))
	UQuestClearNotifyWidget* QuestClearNotifyWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Quest|QuestGiverWidget",meta=(AllowPrivateAccess="true"))
	UQuestGiverWidget* QuestGiverWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Quest|QuestRewardWidget",meta=(AllowPrivateAccess="true"))
	UQuestRewardWidget* QuestRewardWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Quest|QuestGiverWidget",meta=(AllowPrivateAccess="true"))
	UQuestLogWidget* QuestLogWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Quest|QuestTrackerWidget",meta=(AllowPrivateAccess="true"))
	UQuestTrackerWidget* QuestTrackerWidget;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue|DialogueWidget|ZOrder")
	int32 HUDWidgetOrder = 1;
	
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue|DialogueWidget|ZOrder")
	int32 PopupWidgetOrder = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Dialogue|DialogueWidget|ZOrder")
	int32 OverlayWidgetOrder = 2;

	UPROPERTY(BlueprintReadOnly,Category = "Dialogue|DialogueWidget")
	TArray<UUserWidget*> DisplayingWidgets;
public:
	UFUNCTION(BlueprintCallable)
	void AddToViewPort(UUserWidget* InUserWidget,EWarriorWidgetType WidgetType);

	UFUNCTION(BlueprintCallable)
	void RemoveFromViewPort(UUserWidget* InUserWidget);
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsDisplayingWidget(UUserWidget* InUserWidget);
public:
	UFUNCTION()
	FORCEINLINE UWarriorHeroHUD* GetHeroHUD() const { return HUDWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHeroHUD(UWarriorHeroHUD* WarriorHeroHUD) { HUDWidget  = WarriorHeroHUD;}
	
	UFUNCTION()
	FORCEINLINE UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetInventoryWidget(UInventoryWidget* InInventoryWidget) { InventoryWidget  = InInventoryWidget;}
	
	UFUNCTION()
	FORCEINLINE UDialogueOverlayWidget* GetDialogueWidget() const { return DialogueWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDialogueWidget(UDialogueOverlayWidget* InDialogueWidget) { DialogueWidget  = InDialogueWidget;}

	UFUNCTION()
	FORCEINLINE UContainerInventoryWidget* GetContainerInventory() const { return ContainerInventory; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetContainerInventory(UContainerInventoryWidget* InContainerInventory) { ContainerInventory  = InContainerInventory;}

	UFUNCTION()
	FORCEINLINE UQuestClearNotifyWidget* GetQuestClearNotifyWidget() const { return QuestClearNotifyWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQuestClearNotifyWidget(UQuestClearNotifyWidget* InQuestClearNotifyWidget) { QuestClearNotifyWidget = InQuestClearNotifyWidget;}
	
	UFUNCTION()
	FORCEINLINE UQuestGiverWidget* GetQuestGiverWidget() const { return QuestGiverWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQuestGiverWidget(UQuestGiverWidget* InQuestGiverWidget) { QuestGiverWidget = InQuestGiverWidget;}

	UFUNCTION()
	FORCEINLINE UQuestRewardWidget* GetQuestRewardWidget() const { return QuestRewardWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQuestRewardWidget(UQuestRewardWidget* InQuestRewardWidget) { QuestRewardWidget = InQuestRewardWidget;}

	UFUNCTION()
	FORCEINLINE UQuestLogWidget* GetQuestLogWidget() const { return QuestLogWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQuestLogWidget(UQuestLogWidget* InQuestLogWidget) { QuestLogWidget = InQuestLogWidget;}
	
	UFUNCTION()
	FORCEINLINE UQuestTrackerWidget* GetQuestTrackerWidget() const { return QuestTrackerWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetQuestTrackerWidget(UQuestTrackerWidget* InQuestTrackerWidget) { QuestTrackerWidget = InQuestTrackerWidget;}
};
