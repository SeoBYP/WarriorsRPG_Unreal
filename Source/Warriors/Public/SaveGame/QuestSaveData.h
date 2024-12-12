// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SaveGame.h"
#include "QuestSaveData.generated.h"

class UQuestLogComponent;
class AQuestBase;

USTRUCT(Blueprintable,BlueprintType)
struct FQuestSaveDataConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest|SaveData")
	TMap<FString,int32> QuestProgress;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest|SaveData")
	int32 CurrentStage;
};

UCLASS(Blueprintable,BlueprintType)
class WARRIORS_API UQuestSaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BLueprintReadWrite,Category="Quest|SaveData")
	TArray<FName> ActivedQuests;
	
	UPROPERTY(EditDefaultsOnly,BLueprintReadWrite,Category="Quest|SaveData")
	TArray<FName> CompletedQuests;
	
	UPROPERTY(EditDefaultsOnly,BLueprintReadWrite,Category="Quest|SaveData")
	TMap<FName,FQuestSaveDataConfig> QuestProgress;

	UPROPERTY(EditDefaultsOnly,BLueprintReadWrite,Category="Quest|SaveData")
	FName CurrentTrackedQuest;
	

};