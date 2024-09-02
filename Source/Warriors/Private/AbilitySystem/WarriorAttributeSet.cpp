// Vince Petrelli All Rights Reserved


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Interfaces/PawnUIInterface.h"
#include "Utils/WarriorGameplayTags.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"
UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.0f);
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if(!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());

		// 위랑 거의 똑같은 기능
		// CachedPawnUIInterface = Cast<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	
	checkf(CachedPawnUIInterface.IsValid(),TEXT("%s didn't implement IPawnUIInterface"));

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	
	checkf(PawnUIComponent,TEXT(" didn't implement from IPawnUIInterface %s"),*Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	if(Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(),0.f,GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	}

	if(Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(),0.f,GetMaxRage());

		SetCurrentRage(NewCurrentRage);

		if(UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage()/GetMaxRage());
		}
	}

	if(Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone,0.f,GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);


		const FString DebugString = FString::Printf(TEXT("Current health = %f"), NewCurrentHealth);
		Debug::DebugLog(DebugString);
		
		//Notify The UI
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
		
		if(GetCurrentHealth() <= 0.0f)
		{
			UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(
				Data.Target.GetAvatarActor(),
				WarriorsGameplayTags::Shared_Status_Dead
				);
		}
	}
	//Super::PostGameplayEffectExecute(Data);
}
