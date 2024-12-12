// Vince Petrelli All Rights Reserved


#include "Widgets/Dialogue/DialogueOverlayWidget.h"

#include "Systems/DialogueSubSystem.h"

void UDialogueOverlayWidget::BeginDialogue_Implementation(FNPCDataTable NPCInfo, UAudioComponent* InNPCAudio,
                                                          AWarriorNPCCharacter* NPC, const TArray<FDialogueDataTable>& NPCCompletedDialogues)
{
}

void UDialogueOverlayWidget::WaitUntilEndOfSpeech_Implementation()
{
	
}

bool UDialogueOverlayWidget::IsCanShowPlayerResponse_Implementation(AWarriorNPCCharacter* InNPC)
{
	UDialogueSubSystem* DialogueSubSystem =GetWorld()->GetSubsystem<UDialogueSubSystem>();
	if(DialogueSubSystem == nullptr)
	{
		return false;
	}
	// TODO : 플레이어를 따라다니는 상태는 추후에 추가할 예정입니다.
	AvailableDialogueResponses = DialogueSubSystem->GetAvailableDialogueResponses(CurrentDialogueStep,false);
	
	return AvailableDialogueResponses.Num() > 0;
}

void UDialogueOverlayWidget::ShowPlayerResponses_Implementation(AWarriorNPCCharacter* InNPC)
{
	
}

void UDialogueOverlayWidget::ProcessResponse_Implementation(FDialogueResponseDataTable Response)
{
}
