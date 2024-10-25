// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataTables/QuestDataTable.h"
#include "GameFramework/Actor.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "QuestBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestObjectiveUpdated);

UCLASS()
class WARRIORS_API AQuestBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestBase();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true,ExposeOnSpawn=true))
	FName QuestID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	FQuestDataTable QuestDetails;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	int32 CurrentStage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	FStageDetails CurrentStageDetails;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	TMap<FString,int32> CurrentObjectiveProgress;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	bool IsCompleted;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	bool IsTurned;
	
public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable,Category="Quest")
	FOnQuestObjectiveUpdated OnQuestObjectiveUpdated;
};
