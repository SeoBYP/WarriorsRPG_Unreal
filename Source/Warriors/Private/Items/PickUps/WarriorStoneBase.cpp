// Vince Petrelli All Rights Reserved


#include "Items/PickUps/WarriorStoneBase.h"

#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Utils/WarriorGameplayTags.h"

void AWarriorStoneBase::Comsume(UWarriorsAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}

void AWarriorStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                            AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                                            int32 OtherBodyIndex, bool bFromSweep,
                                                            const FHitResult& SweepResult)
{
	if (AWarriorHeroCharacter* OverlapedHeroCharacter = Cast<AWarriorHeroCharacter>(OtherActor))
	{
		OverlapedHeroCharacter->GetWarriorsAbilitySystemComponent()
		                      ->TryActivateAbilityByTag(WarriorsGameplayTags::Player_Ability_PickUp_Stones);
	}
}
