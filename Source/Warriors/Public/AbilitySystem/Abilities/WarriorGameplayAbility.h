// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarriorGameplayAbility.generated.h"

class UPawnCombatComponent;
class UWarriorsAbilitySystemComponent;

UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven,
};
/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	//~ Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	//~ End UGameplayAbility Interface

	//~ Begin UGameplayAbility Interface
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly,Category="WarriorAbilities")
	EWarriorAbilityActivationPolicy AbilityActivationPoliby = EWarriorAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure,Category="Warrior|Abilities")
	UWarriorsAbilitySystemComponent* GetWarriorsAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle InSpecHandle) const;

	UFUNCTION(BlueprintCallable,Category="Warrior|Abilities",meta = (DisplayName = "Apply Game Effect Spec Handle To Target Actor" ,ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle InSpecHandle,EWarriorSuccessType& OutSuccessType);


};
