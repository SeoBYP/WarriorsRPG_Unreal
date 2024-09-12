// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorGameplayAbility.h"
#include "WarriorHeroGameplayAbility.generated.h"

class UHeroUIComponent;
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

	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	UHeroUIComponent* GetHeroUIComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage,
		FGameplayTag InCurrentAttackTypeTag,int32 InCurrentComboCount);

	UFUNCTION(BlueprintCallable,Category="Warrior|Abilities")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InCooldownTag,float& TotalCooldownTime,float& RemainingCooldownTime);
private:
	TWeakObjectPtr<AWarriorHeroCharacter> ChachedWarriorHeroCharacter;
	TWeakObjectPtr<AWarriorsHeroController> ChachedWarriorHeroController;
};
