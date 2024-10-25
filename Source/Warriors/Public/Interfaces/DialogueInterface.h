// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueInterface.generated.h"

class UNPCDialogueComponent;
class UHeroDialogueComponent;
class UPawnDialogueComponent;
// This class does not need to be modified.
UINTERFACE(BlueprintType,Blueprintable)
class UDialogueInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WARRIORS_API IDialogueInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Dialogue")
	void OnRequestStartDialogue();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Dialogue")
	void OnRequestEndDialogue();

	virtual UPawnDialogueComponent* GetPawnDialogueComponent() const;

	virtual UHeroDialogueComponent* GetHeroDialogueComponent() const;

	virtual UNPCDialogueComponent* GetNPCDialogueComponent() const;
};
