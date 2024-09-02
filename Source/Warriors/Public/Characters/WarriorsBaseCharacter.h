// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "WarriorsBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UWarriorAttributeSet;
class UWarriorsAbilitySystemComponent;
class UPawnUIComponent;

UCLASS()
class WARRIORS_API AWarriorsBaseCharacter : public ACharacter,
public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorsBaseCharacter();
	
	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface
protected:

	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,category="AbilitySystem")
	UWarriorsAbilitySystemComponent* WarriorsAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,category="AbilitySystem")
	UWarriorAttributeSet* WarriorAttributeSet;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
	
public:
	FORCEINLINE UWarriorsAbilitySystemComponent* GetWarriorsAbilitySystemComponent() const { return WarriorsAbilitySystemComponent; }
	FORCEINLINE UWarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
};
