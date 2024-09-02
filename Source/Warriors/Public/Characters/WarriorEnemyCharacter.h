// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorsBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;
class UPawnUIComponent;

UCLASS()
class WARRIORS_API AWarriorEnemyCharacter : public AWarriorsBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorEnemyCharacter();
	


	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	//~ End IPawnUIInterface Interface
	
private:
	void InitEnemyStartUpData();
	
protected:

	virtual void BeginPlay() override;
	
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="UI")
	UWidgetComponent* EnemyHealthWidgetComponent;
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemeyCombatComponent() const {return EnemyCombatComponent;}
};

