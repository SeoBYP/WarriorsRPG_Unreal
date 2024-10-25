// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotStruct.generated.h"
/**
 * 
 */
USTRUCT(Blueprintable,BlueprintType)
struct FInventorySlotStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="InventorySlot")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,category="InventorySlot")
	int32 Quantity;
};
