// Vince Petrelli All Rights Reserved


#include "Components/Dialogue/NPCDialogueComponent.h"

#include "BrainComponent.h"
#include "Controllers/WarriorNPCController.h"
#include "WarriorDebugHelper.h"
#include "WarriorGameInstance.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Components/Dialogue/HeroDialogueComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/WarriorWidgetBase.h"

void UNPCDialogueComponent::StartDialogue()
{
	switch (DialogueType)
	{
	case EWarriorDialogueType::BehaviorTree:
		if(AWarriorNPCController* NPCController = GetOwningController<AWarriorNPCController>())
		{
			if (NPCController->GetDiagloueTree())  // GetDiagloueTree()가 nullptr이 아닌지 확인
			{
				NPCController->RunBehaviorTree(NPCController->GetDiagloueTree());
			}
			else
			{
				Debug::DebugLog(TEXT("NPCController's Dialogue Tree is nullptr"));
			}
		}
		else
		{
			Debug::DebugLog(TEXT("AWarriorNPCController Can't Get Controller"));
		}
		break;

	case EWarriorDialogueType::NonBehaviorTree:
		{
			ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if(PlayerCharacter == nullptr)
			{
				Debug::DebugLog(TEXT("PlayerCharacter is nullptr"));
				return;
			}

			if(AWarriorHeroCharacter* HeroCharacter = Cast<AWarriorHeroCharacter>(PlayerCharacter))
			{
				if (HeroCharacter->GetHeroDialogueComponent() != nullptr)
				{
					HeroCharacter->GetHeroDialogueComponent()->OnStartDialogueDelegate.Broadcast(DialogueText, Speaker);
				}
				else
				{
					Debug::DebugLog(TEXT("HeroCharacter's HeroDialogueComponent is nullptr"));
				}
			}
			else
			{
				Debug::DebugLog(TEXT("PlayerCharacter cannot be cast to AWarriorHeroCharacter"));
			}
		}
		break;
	default:
		;
	}
}

void UNPCDialogueComponent::EndDialogue()
{
	switch (DialogueType)
	{
	case EWarriorDialogueType::BehaviorTree:
		if(AWarriorNPCController* NPCController = GetOwningController<AWarriorNPCController>())
		{
			if (NPCController->BrainComponent)
			{
				NPCController->BrainComponent->StopLogic(TEXT("End Dialogue"));
			}
			else
			{
				Debug::DebugLog(TEXT("NPCController's BrainComponent is nullptr"));
			}
		}
		else
		{
			Debug::DebugLog(TEXT("AWarriorNPCController Can't Get Controller"));
		}
		break;

	case EWarriorDialogueType::NonBehaviorTree:
		{
			ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (PlayerCharacter == nullptr)
			{
				Debug::DebugLog(TEXT("PlayerCharacter is nullptr"));
				return;
			}

			if (AWarriorHeroCharacter* HeroCharacter = Cast<AWarriorHeroCharacter>(PlayerCharacter))
			{
				if (HeroCharacter->GetHeroDialogueComponent() != nullptr)
				{
					HeroCharacter->GetHeroDialogueComponent()->OnEndSingleDialogueDelegate.Broadcast();
				}
				else
				{
					Debug::DebugLog(TEXT("HeroCharacter's HeroDialogueComponent is nullptr"));
				}
			}
			else
			{
				Debug::DebugLog(TEXT("PlayerCharacter cannot be cast to AWarriorHeroCharacter"));
			}
		}
		break;
	default: ;
	}
}
