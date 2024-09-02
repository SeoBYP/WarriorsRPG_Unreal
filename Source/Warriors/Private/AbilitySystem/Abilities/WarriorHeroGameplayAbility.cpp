// Vince Petrelli All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Utils/WarriorGameplayTags.h"
#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
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
	return ChachedWarriorHeroController.IsValid() ? ChachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWarriorsAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());
	
	FGameplayEffectSpecHandle EffectSpecHandle = GetWarriorsAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		WarriorsGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage);

	if(InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag,InUsedComboCount);
	}
	
	return EffectSpecHandle;
}
