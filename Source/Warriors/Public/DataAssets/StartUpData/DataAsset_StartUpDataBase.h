// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarriorsAbilitySystemComponent;
class UWarriorGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class WARRIORS_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorsAbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
	
	void GrantAbilities(const TArray< TSubclassOf < UWarriorGameplayAbility > >& InAbilitiesToGive,UWarriorsAbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1);
};
