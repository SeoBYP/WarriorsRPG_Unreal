// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WarriorWidgetBase.h"
#include "ContainerInventoryWidget.generated.h"

class UInventoryComponent;
/**
 * 
 */
UCLASS()
class WARRIORS_API UContainerInventoryWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inventory",meta=(AllowPrivateAccess=true))
	UInventoryComponent* ContainerInventory;
	
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnInitialzieContainerInventoryWidget(UInventoryComponent* InContainerInventory);

	UFUNCTION()
	FORCEINLINE UInventoryComponent* GetContainerInventory() const {return ContainerInventory;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetContainerInventory(UInventoryComponent* InContainerInventory) { ContainerInventory = InContainerInventory;}
};
