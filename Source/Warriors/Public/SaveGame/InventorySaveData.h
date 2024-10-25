// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/InventoryComponent.h"
#include "GameFramework/SaveGame.h"
#include "InventorySaveData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class WARRIORS_API UInventorySaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory")
	TArray<FInventorySlotStruct> InventoryContents;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Inventory")
	TArray<int32> HotbarContents;
};
