﻿// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"


class AWarriorHeroWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	AWarriorHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	AWarriorHeroWeapon* GetHeroCarriedEquippedWeapon() const;

	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	float GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const;
	
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
