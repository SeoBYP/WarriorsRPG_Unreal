// Vince Petrelli All Rights Reserved


#include "Warriors/Public/Characters/WarriorHeroCharacter.h"
#include "Warriors/Public/WarriorDebugHelper.h"

// Sets default values
AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::DebugLog(TEXT("Hello World"));
}

// Called every frame
void AWarriorHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

