// Vince Petrelli All Rights Reserved


#include "AbilitySystem/WarriorsAbilitySystemComponent.h"

void UWarriorsAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
			continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWarriorsAbilitySystemComponent::OnAbilityInputRealesed(const FGameplayTag& InInputTag)
{
}
