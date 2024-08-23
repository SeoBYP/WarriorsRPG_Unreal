// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "WarriorsBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "WarriorHeroCharacter.generated.h"

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
	
	
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,category="Character Data",meta=(AllowPrivateAccess="true"))
	UDataAsset_InputConfig* InputConfigDataConfig;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look(const FInputActionValue& InputActionValue);
#pragma endregion 

	
public:

	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
