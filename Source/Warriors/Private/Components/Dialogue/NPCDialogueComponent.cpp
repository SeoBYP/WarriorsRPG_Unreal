// Vince Petrelli All Rights Reserved


#include "Components/Dialogue/NPCDialogueComponent.h"

#include "BrainComponent.h"
#include "Controllers/WarriorNPCController.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameInstance.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Characters/NPC/WarriorNPCCharacter.h"
#include "Components/Dialogue/HeroDialogueComponent.h"
#include "Components/Quest/QuestGiverComponent.h"
#include "Components/Quest/QuestLogComponent.h"
#include "DataTables/DialogueDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestBase.h"
#include "Systems/DialogueSubSystem.h"
#include "Widgets/WarriorWidgetBase.h"

// void UNPCDialogueComponent::StartDialogue()
// {
// 	// if(AWarriorNPCController* NPCController = GetOwningController<AWarriorNPCController>())
// 	// {
// 	// 	if (NPCController->GetDiagloueTree())  // GetDiagloueTree()가 nullptr이 아닌지 확인
// 	// 	{
// 	// 		NPCController->RunBehaviorTree(NPCController->GetDiagloueTree());
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		Debug::DebugLog(TEXT("NPCController's Dialogue Tree is nullptr"));
// 	// 	}
// 	// }
// 	// else
// 	// {
// 	// 	Debug::DebugLog(TEXT("AWarriorNPCController Can't Get Controller"));
// 	// }
// }


// void UNPCDialogueComponent::EndDialogue()
// {
// 	// if(AWarriorNPCController* NPCController = GetOwningController<AWarriorNPCController>())
// 	// {
// 	// 	if (NPCController->BrainComponent)
// 	// 	{
// 	// 		NPCController->BrainComponent->StopLogic(TEXT("End Dialogue"));
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		Debug::DebugLog(TEXT("NPCController's BrainComponent is nullptr"));
// 	// 	}
// 	// }
// 	// else
// 	// {
// 	// 	Debug::DebugLog(TEXT("AWarriorNPCController Can't Get Controller"));
// 	// }
// }



FDialogueDataTable UNPCDialogueComponent::GetDialogueDataTable()
{
	UDialogueSubSystem* DialogueSubSystem = GetWorld()->GetSubsystem<UDialogueSubSystem>();
	if (!ensure(DialogueSubSystem))
	{
		Debug::Log(TEXT(" UNPCDialogueComponent::GetDialogueStepDataTable => DialogueSubSystem is null"));
		return FDialogueDataTable();
	}

	UDataTable* DialogueDataTable = DialogueSubSystem->GetDialogueDataTable();
	if (!ensure(DialogueDataTable))
	{
		Debug::Log(TEXT(" UNPCDialogueComponent::GetDialogueStepDataTable => DialogueDataTable is null"));
		return FDialogueDataTable();
	}
	
	if(AWarriorNPCCharacter* NPCCharacter = SafeGetOwnerPawn<AWarriorNPCCharacter>())
	{
		FName CurrentQuestID = NPCCharacter->GetQuestGiverComponent()->GetQuestDataTableRowName();
		EDialogueType CurrentDialogueType = GetDialogueType();
		
		TArray<FDialogueDataTable*> DialogueDataTables;
		DialogueDataTable->GetAllRows<FDialogueDataTable>(TEXT("Can't Get FDialogueDataTable"),DialogueDataTables);
		for(FDialogueDataTable* dialogueData : DialogueDataTables)
		{
			// NPC가 다르면 생략
			if(dialogueData->NPCID != NPCCharacter->GetNPCID()) continue;
			// NPC의 퀘스트 가 다르면 생략
			if(dialogueData->RelatedQuestID != CurrentQuestID) continue;
			// NPC의 현재 Dialogue 타입과 다르면 생략
			if(dialogueData->DialogueType != CurrentDialogueType) continue;

			return *dialogueData;
		}
	}
	return FDialogueDataTable{};
}

EDialogueType UNPCDialogueComponent::GetDialogueType()
{
	AWarriorHeroCharacter* WarriorHeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld());
	if (!ensure(WarriorHeroCharacter))
	{
		Debug::Log(TEXT("Warrior Hero Character Is Null"));
		return EDialogueType::EDT_MAX;
	}
	UQuestLogComponent* QuestLogComponent = WarriorHeroCharacter->GetQuestLogComponent();
	if (!ensure(QuestLogComponent))
	{
		Debug::Log(TEXT("Quest Log Component Is Null"));
		return EDialogueType::EDT_MAX;
	}

	if(AWarriorNPCCharacter* NPCCharacter = SafeGetOwnerPawn<AWarriorNPCCharacter>())
	{
		if(!NPCCharacter->GetQuestGiverComponent()->HasQuest())
		{
			return EDialogueType::EDT_InformationOnly;
		}
		FName QuestID = NPCCharacter->GetQuestGiverComponent()->GetQuestDataTableRowName();

		bool bIsTurnedIn = false;
		bool bIsActiveQuest = QuestLogComponent->QueryActiveQuest(QuestID);
		bool bIsCompoleteQuest = QuestLogComponent->QueryCompletedQuests(QuestID, bIsTurnedIn);
		// 퀘스트 시작 해야 함
		if (!bIsActiveQuest && !bIsCompoleteQuest)
		{
			return EDialogueType::EDT_QuestAvailable;
		}
		// 퀘스트 진행중
		else if(bIsActiveQuest && !bIsCompoleteQuest)
		{
			return EDialogueType::EDT_QuestInProgress;
		}
		// 퀘스트 끝남
		else if(bIsActiveQuest && bIsCompoleteQuest)
		{
			if (AQuestBase* Quest = QuestLogComponent->GetQuestActor(QuestID))
			{
				// 퀘스트 보상을 안 받은
				if (Quest->GetIsCompleted() && !Quest->GetIsTurned())
				{
					return EDialogueType::EDT_QuestCompleted;
				}
				// 이미 보상까지 다 받은
				else
				{
					return EDialogueType::EDT_QuestFinished;
				}
			}
		}
	}
	return EDialogueType::EDT_MAX;
}
