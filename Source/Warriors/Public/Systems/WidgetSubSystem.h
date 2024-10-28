// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "WidgetSubSystem.generated.h"

class UDialogueWidget;
class UInventoryWidget;
class UWarriorHeroHUD;
/**
 * 
 */
UCLASS()
class WARRIORS_API UWidgetSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;  // 필요한 경우 레벨 전환 시 수행할 작업을 추가

protected:
	UPROPERTY(BlueprintReadOnly, Category = "HeroHUD",meta=(AllowPrivateAccess="true"))
	UWarriorHeroHUD* HeroHUDWidget;

	UPROPERTY(BlueprintReadOnly, Category = "InventoryWidget",meta=(AllowPrivateAccess="true"))
	UInventoryWidget* HeroInventoryWidget;

	UPROPERTY(BlueprintReadOnly, Category = "ContainerInventory",meta=(AllowPrivateAccess="true"))
	UContainerInventory* HeroContainerInventory;
	
	UPROPERTY(BlueprintReadOnly, Category = "DialogueWidget",meta=(AllowPrivateAccess="true"))
	UDialogueWidget* HeroDialogueWidget;

public:
	UFUNCTION()
	FORCEINLINE UWarriorHeroHUD* GetHeroHUD() { return HeroHUDWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetHeroHUD(UWarriorHeroHUD* WarriorHeroHUD) { HeroHUDWidget  = WarriorHeroHUD;}
	
	UFUNCTION()
	FORCEINLINE UInventoryWidget* GetInventoryWidget() { return HeroInventoryWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetInventoryWidget(UInventoryWidget* InventoryWidget) { HeroInventoryWidget  = InventoryWidget;}
	
	UFUNCTION()
	FORCEINLINE UDialogueWidget* GetDialogueWidget() { return HeroDialogueWidget; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetDialogueWidget(UDialogueWidget* DialogueWidget) { HeroDialogueWidget  = DialogueWidget;}

	UFUNCTION()
	FORCEINLINE UContainerInventory* GetContainerInventory() { return HeroContainerInventory; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetContainerInventory(UContainerInventory* ContainerInventory) { HeroContainerInventory  = ContainerInventory;}
};
