// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "WarriorsBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/DialogueInterface.h"
#include "WarriorHeroCharacter.generated.h"

class UInventoryComponent;
class UInteractorComponent;
class UHeroDialogueComponent;class UHeroUIComponent;
class UPawnUIComponent;
class UHeroCombatComponent;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;

//TODO : 추후 QuestLog 혹은 Interface와 통합할 예정
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestObjectiveID,FString, ObjectiveID,int32, Value = 1);

UCLASS()
class WARRIORS_API AWarriorHeroCharacter : public AWarriorsBaseCharacter,
public IDialogueInterface
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
	
	virtual UHeroDialogueComponent* GetHeroDialogueComponent() const override;
	
protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category="Combat", meta=(AllowPrivateAccess="true"))
	UHeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category="Combat", meta=(AllowPrivateAccess="true"))
	UHeroUIComponent* HeroUIComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Dialogue", meta=(AllowPrivateAccess="true"))
	UHeroDialogueComponent* HeroDialogueComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Interaction", meta=(AllowPrivateAccess="true"))
	UInteractorComponent* InteractorComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Inventory", meta=(AllowPrivateAccess="true"))
	UInventoryComponent* InventoryComponent;
#pragma endregion

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category="Character Data", meta=(AllowPrivateAccess="true"))
	UDataAsset_InputConfig* InputConfigDataConfig;

	UPROPERTY()
	FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggerd(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputRealesed(FGameplayTag InInputTag);
#pragma endregion

#pragma region Delegates
public:
	// Objective 아이디 Delegate
	UPROPERTY(BlueprintCallable,BlueprintAssignable, Category="Quest|Objective")
	FOnRequestObjectiveID OnRequestObjectiveID;
#pragma endregion 
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }
	FORCEINLINE UInteractorComponent* GetInteractorComponent() const {return InteractorComponent;}
	FORCEINLINE UInventoryComponent* GetUInventoryComponent() const {return InventoryComponent;}
};
