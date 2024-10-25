// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "QuestDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FQuestDataTable: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText QuestName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText LogDescription;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText TrackingDescription;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bIsMainQuest;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FStageDetails> Stages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bAutoAccept;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool bAutoComplete;
};