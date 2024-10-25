﻿// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractionIndicator.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UInteractionIndicator : public UUserWidget,public IInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite,Category="Components|Interaction",meta=(allowPrivateAccess=true))
	UInteractableComponent* OwnerInteractable;
};
