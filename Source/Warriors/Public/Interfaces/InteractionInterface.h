// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Interaction/InteractableComponent.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Blueprintable)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WARRIORS_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Interaction")
	void InitializeReference(UInteractableComponent* InteractableComponent);

	// UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction|ToInteract")
	// void InteractRequest();

	// UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction|ToInteract")
	// void LookAt();
	//
	// UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction|ToInteract")
	// void InteractWith(FString& OutObjectiveID);
};
