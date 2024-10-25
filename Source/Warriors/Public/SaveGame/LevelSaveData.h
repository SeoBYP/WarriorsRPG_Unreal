// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Inventory/InventoryComponent.h"
#include "GameFramework/SaveGame.h"
#include "Inventory/ContainerStruct.h"
#include "LevelSaveData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class WARRIORS_API ULevelSaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="SaveGame")
	TArray<TSoftObjectPtr<AActor>> ActorsRemoved;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="SaveGame")
	TMap<TSoftClassPtr<AActor>,FTransform> ActorsAdded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="SaveGame")
	TMap<TSoftObjectPtr<UInventoryComponent>,FContainerStruct> ContainersAdded;
};
