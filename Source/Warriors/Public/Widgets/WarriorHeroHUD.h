// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorWidgetBase.h"
#include "WarriorHeroHUD.generated.h"

class UHeroDialogueComponent;
/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorHeroHUD : public UWarriorWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	// UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName = "On Owning Hero HUD Dialogue Initialized"))
	// void BP_OnOwningHeroHUDDialogueInitialized(UHeroDialogueComponent* OwningHeroDialogueComponent);
};
