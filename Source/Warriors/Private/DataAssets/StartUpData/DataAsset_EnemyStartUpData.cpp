// Vince Petrelli All Rights Reserved


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "WarriorTypes/WarriorStructTypes.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorsAbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if(!EnemyCombatAbilities.IsEmpty()){
		for (const TSubclassOf<UWarriorEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if(!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
