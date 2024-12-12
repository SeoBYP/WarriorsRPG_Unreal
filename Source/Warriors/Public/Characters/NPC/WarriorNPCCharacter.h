// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataTables/NPCDataTable.h"
#include "GameFramework/Character.h"
#include "Interfaces/DialogueInterface.h"
#include "WarriorNPCCharacter.generated.h"

class UBehaviorTree;
class UInteractableComponent;
class UQuestGiverComponent;

UCLASS()
class WARRIORS_API AWarriorNPCCharacter : public ACharacter //, public IDialogueInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorNPCCharacter();
protected:
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	
	void UpdateNPCProperties();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NPC|Dialogue", meta=(AllowPrivateAccess="true"))
	UNPCDialogueComponent* NPCDialogueComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NPC|Dialogue", meta=(AllowPrivateAccess="true"))
	UQuestGiverComponent* QuestGiverComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NPC|Interactable", meta=(AllowPrivateAccess="true"))
	UInteractableComponent* InteractableComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="NPC|Properties", meta=(AllowPrivateAccess="true"))
	FDataTableRowHandle NPCDataTableRowHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="NPC|Properties", meta=(AllowPrivateAccess="true"))
	FNPCDataTable NPCDataTable;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="NPC|Properties", meta=(AllowPrivateAccess="true"))
	// FString NPCID;
	//
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="NPC|Properties", meta=(AllowPrivateAccess="true"))
	// FText NPCName;
	//
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="NPC|Properties", meta=(AllowPrivateAccess="true"))
	// ENPCType NPCType;
	//
	// UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="NPC|Properties", meta=(AllowPrivateAccess="true"))
	// ENPCSubType NPCSubType;

public:
	UFUNCTION()
	FORCEINLINE UNPCDialogueComponent* GetNPCDialogueComponent() const {return NPCDialogueComponent;}
	UFUNCTION()
	FORCEINLINE UQuestGiverComponent* GetQuestGiverComponent() const {return QuestGiverComponent;}

	FORCEINLINE FString GetNPCID() const { return NPCDataTable.ID;}
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="NPC|Properties")
	FORCEINLINE FText GetNPCName() const { return NPCDataTable.Name;}
};
