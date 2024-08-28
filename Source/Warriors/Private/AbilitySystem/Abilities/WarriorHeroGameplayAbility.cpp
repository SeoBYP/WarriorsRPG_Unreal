// Vince Petrelli All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorsHeroController.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!ChachedWarriorHeroCharacter.IsValid())
	{
		ChachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return ChachedWarriorHeroCharacter.IsValid()? ChachedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorsHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!ChachedWarriorHeroController.IsValid())
	{
		ChachedWarriorHeroController = Cast<AWarriorsHeroController>(CurrentActorInfo->PlayerController);
	}
	return ChachedWarriorHeroCharacter.IsValid() ? ChachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
