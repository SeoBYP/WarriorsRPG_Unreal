// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "WarriorsBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "WarriorHeroCharacter.generated.h"

class UHeroUIComponent;
class UPawnUIComponent;
class UHeroCombatComponent;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;

UCLASS()
class WARRIORS_API AWarriorHeroCharacter : public AWarriorsBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorHeroCharacter();
	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UHeroUIComponent* GetHeroUIComponent() const override;
	//~ End IPawnUIInterface Interface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="Camera",meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="Camera",meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="Combat",meta=(AllowPrivateAccess="true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="Combat",meta=(AllowPrivateAccess="true"))
	UHeroUIComponent* HeroUIComponent;
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,category="Character Data",meta=(AllowPrivateAccess="true"))
	UDataAsset_InputConfig* InputConfigDataConfig;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputRealesed(FGameplayTag InInputTag);
#pragma endregion 
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
};
