// Vince Petrelli All Rights Reserved


#include "Widgets/WarriorHeroHUD.h"

#include "Components/Dialogue/HeroDialogueComponent.h"
#include "Interfaces/DialogueInterface.h"

void UWarriorHeroHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// if(IDialogueInterface* DialogueInterface = Cast<IDialogueInterface>(GetOwningPlayerPawn()))
	// {
	// 	if(UHeroDialogueComponent* HeroDialogueComponent = DialogueInterface->GetHeroDialogueComponent())
	// 	{
	// 		BP_OnOwningHeroHUDDialogueInitialized(HeroDialogueComponent);
	// 	}
	// }
}
