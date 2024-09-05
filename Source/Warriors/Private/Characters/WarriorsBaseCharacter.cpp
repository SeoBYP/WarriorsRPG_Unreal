// Vince Petrelli All Rights Reserved


#include "Warriors/Public/Characters/WarriorsBaseCharacter.h"
#include "Warriors/Public/AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "Warriors/Public/AbilitySystem/WarriorAttributeSet.h"
#include "MotionWarpingComponent.h"
// Sets default values
AWarriorsBaseCharacter::AWarriorsBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	WarriorsAbilitySystemComponent = CreateDefaultSubobject<UWarriorsAbilitySystemComponent>(TEXT("WarriorsAbilitySystemComponent"));

	WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));
	
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* AWarriorsBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorsAbilitySystemComponent();
}

UPawnCombatComponent* AWarriorsBaseCharacter::GetPawnCombatComponent() const
{
	return  nullptr;
}

UPawnUIComponent* AWarriorsBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AWarriorsBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(WarriorsAbilitySystemComponent)
	{
		WarriorsAbilitySystemComponent->InitAbilityActorInfo(this,this);
		
		ensureMsgf(!CharacterStartUpData.IsNull(),TEXT("CharacterStartUpData is NULL to %s"),*GetName());
	}
}


