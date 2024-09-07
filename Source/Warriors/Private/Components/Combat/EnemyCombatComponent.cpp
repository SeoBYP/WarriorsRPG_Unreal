// Vince Petrelli All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Utils/WarriorGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverllapedActors.Contains(HitActor))
	{
		return;
	}

	OverllapedActors.AddUnique(HitActor);

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHaveTag(HitActor,WarriorsGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UWarriorFunctionLibrary::IsValidBlock(GetOwningPawn(),HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			WarriorsGameplayTags::Player_Event_SuccessfulBlock,
			EventData
			);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorsGameplayTags::Shared_Event_MeleeHit,
			EventData);
	}
}
