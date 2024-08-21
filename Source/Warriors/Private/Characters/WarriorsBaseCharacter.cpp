// Vince Petrelli All Rights Reserved


#include "Warriors/Public/Characters/WarriorsBaseCharacter.h"


// Sets default values
AWarriorsBaseCharacter::AWarriorsBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
	
}


