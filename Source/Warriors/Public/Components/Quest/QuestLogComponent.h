// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "QuestLogComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted,AQuestBase*,QuestActor);
class AQuestBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),BlueprintType,Blueprintable)
class WARRIORS_API UQuestLogComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	TArray<FName> CurrentActiveQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	TArray<FName> CompletedQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	FName CurrentTrackedQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	TArray<AQuestBase*> CurrentQuests;

public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable,Category="Quest|Action")
	FOnQuestCompleted OnQuestCompleted;

	//TODO : 추후 Delegate 방식으로 변환 여부 검토
	// UPROPERTY(BlueprintCallable,BlueprintAssignable,Category="Quest|Action")
	// FOnQuestUpdated OnQuestUpdated;
public:
	UFUNCTION(BlueprintCallable)
	void SaveQuestData();
	
	UFUNCTION(BlueprintCallable)
	AQuestBase* AddNewQuest(FName QuestID);

	UFUNCTION(BlueprintCallable)
	void CompleteQuest(FName QuestID);

	UFUNCTION(BlueprintCallable)
	void TrackQuest(AQuestBase* QuestActor);

	UFUNCTION(BlueprintCallable)
	AQuestBase* GetQuestActor(FName QuestID);

	UFUNCTION(BlueprintCallable)
	void TurnInQuest(FName QuestID);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool QueryActiveQuest(FName QuestID);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool QueryCompletedQuests(FName QuestID,bool& TurnedIn);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsQuestFailed(FString QuestID);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsQuestFinished(FString QuestID);
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsQuestCompleted(FString QuestID);

	UFUNCTION(BlueprintCallable,BlueprintPure)
	bool IsQuestStarted(FString QuestID);
	
public:
	FORCEINLINE TArray<FName> GetCurrentActiveQuests() { return CurrentActiveQuests; }
	FORCEINLINE void SetCurrentActiveQuest(const TArray<FName>& InCurrentActiveQuests) { CurrentActiveQuests = InCurrentActiveQuests; }
	FORCEINLINE TArray<FName> GetCompletedQuests() { return CompletedQuests; }
	FORCEINLINE void SetCompletedQuests(const TArray<FName>& InCompletedQuests) {CompletedQuests = InCompletedQuests;}
};
