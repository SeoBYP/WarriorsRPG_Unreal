// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "StageDetails.h"
#include "DataTables/QuestDataTable.h"
#include "GameFramework/Actor.h"
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
	virtual void BeginPlay() override;

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
	bool bIsCompleted;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Quest",meta=(AllowPrivateAccess=true))
	bool bIsTurned;
	
public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable,Category="Quest")
	FOnQuestObjectiveUpdated OnQuestObjectiveUpdated;

public:
	UFUNCTION(BlueprintCallable)
	void OnObjectiveIDHeard(FString ObjectiveID, int32 Value);
	
	UFUNCTION(BlueprintCallable)
	void GetQuestDetails();

	UFUNCTION(BlueprintCallable,BlueprintPure)
	FObjectiveDetails GetObjectiveDataByID(FString ObjectiveID);

	UFUNCTION(BlueprintCallable)
	void CheckObjectiveComplete(FString ObjectiveID);

	UFUNCTION(BlueprintCallable)
	bool AreObjectivesComplete(); 
	
public:
	FORCEINLINE bool GetIsTurned() const {return bIsTurned;}
	FORCEINLINE void SetIsTurned(bool InIsTurned) {bIsTurned = InIsTurned;}
	
	FORCEINLINE bool GetIsCompleted() const { return bIsCompleted; }
	FORCEINLINE void SetIsCompleted(bool InIsCompleted) {bIsCompleted = InIsCompleted;}

	FORCEINLINE FName GetQuestID() const { return QuestID;}
	FORCEINLINE void SetQuestID(FName InQuestID) { QuestID = InQuestID; }

	FORCEINLINE FStageDetails GetCurrentStageDetails() const { return CurrentStageDetails; }

	FORCEINLINE int32 GetCurrentStage() const { return CurrentStage; }
	FORCEINLINE void SetCurrentStage(int32 InCurrentStage) { CurrentStage = InCurrentStage; }

	FORCEINLINE TMap<FString,int32> GetCurrentObjectiveProgress() const {return CurrentObjectiveProgress;}
	FORCEINLINE void SetCurrentObjectiveProgress(const TMap<FString,int32>& InCurrentObjectiveProgress) {CurrentObjectiveProgress = InCurrentObjectiveProgress;}
};
