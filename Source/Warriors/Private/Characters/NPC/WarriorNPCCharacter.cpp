// Vince Petrelli All Rights Reserved


#include "Characters/NPC/WarriorNPCCharacter.h"
#include "Components/Dialogue/NPCDialogueComponent.h"
#include "WarriorDebugHelper.h"

// Sets default values
AWarriorNPCCharacter::AWarriorNPCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NPCDialogueComponent = CreateDefaultSubobject<UNPCDialogueComponent>(TEXT("NPCDialogueComponent"));
}

UNPCDialogueComponent* AWarriorNPCCharacter::GetNPCDialogueComponent() const
{
	return NPCDialogueComponent;
}
