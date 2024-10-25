// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DialogueInterface.h"
#include "WarriorNPCCharacter.generated.h"

UCLASS()
class WARRIORS_API AWarriorNPCCharacter : public ACharacter, public IDialogueInterface
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AWarriorNPCCharacter();
	
	//~ Begin IDialogueInterface Interface
	// virtual void OnRequestStartDialogue_Implementation() override;
	// virtual void OnRequestEndDialogue_Implementation() override;
	// virtual UPawnDialogueComponent* GetPawnDialogueComponent() const override;
	virtual UNPCDialogueComponent* GetNPCDialogueComponent() const override;
	//~ End IDialogueInterface Interface

	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Dialogue", meta=(AllowPrivateAccess="true"))
	UNPCDialogueComponent* NPCDialogueComponent;
	
};
