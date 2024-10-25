// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InventorySlotStruct.h"
#include "ContainerStruct.generated.h"
/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FContainerStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Container")
	TArray<FInventorySlotStruct> Contents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category="Container")
	FTransform Transform;
};
