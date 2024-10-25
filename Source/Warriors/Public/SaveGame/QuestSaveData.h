// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSaveData.generated.h"

USTRUCT(Blueprintable,BlueprintType)
struct FQuestSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest|SaveData")
	TMap<FString,int32> QuestProgress;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest|SaveData")
	int32 CurrentStage;
};