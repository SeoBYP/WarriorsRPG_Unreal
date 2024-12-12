// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Quest/QuestLogComponent.h"
#include "DataTables/DialogueDataTable.h"
#include "DataTables/DialogueResponseDataTable.h"
#include "DataTables/DialogueStepDataTable.h"
#include "DataTables/NPCDataTable.h"
#include "Subsystems/Subsystem.h"
#include "DialogueSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UDialogueSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Dialogue",meta=(AllowPrivateAccess=true))
	UDataTable* DialogueDataTable;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Dialogue",meta=(AllowPrivateAccess=true))
	UDataTable* DialogueStepDataTable;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Data | Quest",meta=(AllowPrivateAccess))
	UDataTable* DialogueResponseDataTable;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Dialogue",meta=(AllowPrivateAccess=true))
	TArray<FDialogueDataTable> DialogueDataArray;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Dialogue",meta=(AllowPrivateAccess=true))
	TArray<FDialogueStepDataTable> DialogueStepDataArray;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Dialogue",meta=(AllowPrivateAccess=true))
	TArray<FDialogueResponseDataTable> DialogueResponseDataArray;
private:
	FNPCDataTable CachedNPC;
	TArray<FDialogueDataTable> CachedCompletedDialogues;
	FDialogueDataTable CachedLocalDialogue;
	UQuestLogComponent* CachedQuestLogComponent;
private:
	UFUNCTION()
	void LoadDialogueDataTable();
	
	UFUNCTION()
	void LoadDialogueStepDataTable();

	UFUNCTION()
	void LoadDialogueResponseDataTable();

	bool IsQuestFailedDialogue() const;

	bool IsQuestFinishedDialogue();

	bool IsQuestCompletedDialogue();

	bool IsQuestProgressDialogue();

	bool IsQuestAvailableDialogue();

	bool IsFollowerDialogue();
	
	bool IsOtherDialogue();

public:
	UFUNCTION(BlueprintCallable,Category="Dialogue|Step")
	FDialogueStepDataTable GetStepDataTableByIndex(FString DialogueID,int32 Index);

	UFUNCTION(BlueprintCallable,Category="Dialogue|Step")
	FDialogueStepDataTable GetStepDataTableByPrerequisite(FString DialogueID,FString PrerequisiteResponseID);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Dialogue")
	FDialogueDataTable GetDialogueByNPC(FNPCDataTable NPC,TArray<FDialogueDataTable> CompletedDialogues);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Dialogue")
	FDialogueStepDataTable GetDialogueStepByDialogueAndResponse(FDialogueDataTable Dialogue
		, FDialogueResponseDataTable Response,bool CharismaCheckSucceeded);
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Dialogue")
	FDialogueStepDataTable GetDialogueStepbyDialogueandPreviousDialogueStep(
		FDialogueDataTable Dialogue,FDialogueStepDataTable PreviousDialogueStep);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Dialogue")
	TArray<FDialogueResponseDataTable> GetAvailableDialogueResponses(
		FDialogueStepDataTable DialogueStep, bool IsNPCFollowingPlayer);
	
public:
	FORCEINLINE UDataTable* GetDialogueDataTable() const { return DialogueDataTable; }
	FORCEINLINE UDataTable* GetDialogueStepDataTable() const { return DialogueStepDataTable; }
	FORCEINLINE UDataTable* GetDialogueResponseDataTable() const { return DialogueResponseDataTable; }
	
};
