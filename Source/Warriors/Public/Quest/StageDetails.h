// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ObjectiveDetails.h"
#include "UObject/Object.h"
#include "StageDetails.generated.h"

USTRUCT(BlueprintType,Blueprintable)
struct FStageDetails
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText StageName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FObjectiveDetails> Objectives;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 XPReward;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TMap<FName,int32> ItemRewards;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 CurrencyRewards;
};
