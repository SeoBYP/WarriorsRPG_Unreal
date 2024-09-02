// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UWarriorEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIORS_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
	virtual void GiveToAbilitySystemComponent(UWarriorsAbilitySystemComponent* InASCToGive,int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAbilities;
};
