// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorsAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorsAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputRealesed(const FGameplayTag& InInputTag);
};
