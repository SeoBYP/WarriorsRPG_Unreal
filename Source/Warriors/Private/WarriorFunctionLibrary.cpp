// Vince Petrelli All Rights Reserved


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

UWarriorsAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UWarriorsAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));;
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UWarriorsAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }
}

void UWarriorFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    UWarriorsAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }
}

bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UWarriorsAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType)
{
    OutConfirmType = NativeDoesActorHaveTag(InActor,TagToCheck)? EWarriorConfirmType::YES : EWarriorConfirmType::NO;
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFormActor(AActor* InActor)
{
    check(InActor);

    if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return  PawnCombatInterface->GetPawnCombatComponent();
    }
    return  nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFormActor(AActor* InActor,
    EWarriorVaildType& OutVaildType)
{
    UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFormActor(InActor);
    OutVaildType = CombatComponent ? EWarriorVaildType::Vaild : EWarriorVaildType::Invalid;
    return CombatComponent;
}