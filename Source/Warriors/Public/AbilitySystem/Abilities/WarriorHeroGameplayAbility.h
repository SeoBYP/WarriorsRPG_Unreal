﻿// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorGameplayAbility.h"
#include "WarriorHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AWarriorsHeroController;
class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	AWarriorHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	AWarriorsHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
private:
	TWeakObjectPtr<AWarriorHeroCharacter> ChachedWarriorHeroCharacter;
	TWeakObjectPtr<AWarriorsHeroController> ChachedWarriorHeroController;
};
