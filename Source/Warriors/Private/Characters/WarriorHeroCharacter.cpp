// Vince Petrelli All Rights Reserved


#include "Warriors/Public/Characters/WarriorHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/WarriorInputComponent.h"
#include "Warriors/Public/DataAssets/Input/DataAsset_InputConfig.h"
#include "Warriors/Public/Utils/WarriorGameplayTags.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "WarriorDebugHelper.h"
#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/Dialogue/HeroDialogueComponent.h"
#include "Components/Interaction/InteractorComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Components/Quest/QuestLogComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "GameModes/WarriorsBaseGameMode.h"

// Sets default values
AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
	//HeroDialogueComponent = CreateDefaultSubobject<UHeroDialogueComponent>(TEXT("HeroDialogueComponent"));
	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>(TEXT("InteractorComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	QuestLogComponent = CreateDefaultSubobject<UQuestLogComponent>(TEXT("QuestLogComponent"));
}

UPawnCombatComponent* AWarriorHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* AWarriorHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* AWarriorHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

// UHeroDialogueComponent* AWarriorHeroCharacter::GetHeroDialogueComponent() const
// {
// 	return HeroDialogueComponent;
// }

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//SoftObjectPtr에서는 IsValid는 이미 로드된 상태를 의미한다.
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;

			if (AWarriorsBaseGameMode* GameMode = GetWorld()->GetAuthGameMode<AWarriorsBaseGameMode>())
			{
				switch (GameMode->GetWarriorGameDifficulty())
				{
				case EWarriorGameDifficulty::Easy:
					AbilityApplyLevel = 4;
					break;
				case EWarriorGameDifficulty::Normal:
					AbilityApplyLevel = 3;
					break;
				case EWarriorGameDifficulty::Hard:
					AbilityApplyLevel = 2;
					break;
				case EWarriorGameDifficulty::VeryHard:
					AbilityApplyLevel = 1;
					break;
				}
			}
			Debug::Log(TEXT("Current Game Difficulty : %f"),AbilityApplyLevel);
			LoadedData->GiveToAbilitySystemComponent(WarriorsAbilitySystemComponent,AbilityApplyLevel);
		}
	}
}

// Called to bind functionality to input
void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataConfig, TEXT("Forget to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataConfig->DefaultMappingContext, 0);

	UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataConfig, WarriorsGameplayTags::InputTag_Move,
	                                             ETriggerEvent::Triggered, this, &AWarriorHeroCharacter::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataConfig, WarriorsGameplayTags::InputTag_Look,
	                                             ETriggerEvent::Triggered, this, &AWarriorHeroCharacter::Input_Look);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataConfig, WarriorsGameplayTags::InputTag_SwitchTarget,
	                                             ETriggerEvent::Triggered, this,
	                                             &ThisClass::Input_SwitchTargetTriggerd);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataConfig, WarriorsGameplayTags::InputTag_SwitchTarget,
	                                             ETriggerEvent::Completed, this,
	                                             &ThisClass::Input_SwitchTargetCompleted);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataConfig, WarriorsGameplayTags::InputTag_PickUp_Stones,
	                                             ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);

	WarriorInputComponent->BindAbilityInputAction(InputConfigDataConfig, this, &ThisClass::Input_AbilityInputPressed,
	                                              &AWarriorHeroCharacter::Input_AbilityInputRealesed);
}

// Called when the game starts or when spawned
void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}

	// if(HeroDialogueComponent)
	// 	HeroDialogueComponent->DialogueInteractCheck(FollowCamera);
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWarriorHeroCharacter::Input_SwitchTargetTriggerd(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AWarriorHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f
			? WarriorsGameplayTags::Player_Event_SwitchTarget_Right
			: WarriorsGameplayTags::Player_Event_SwitchTarget_Left,
		Data);
}

void AWarriorHeroCharacter::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;


	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		WarriorsGameplayTags::Player_Event_ComsumeStones,
		Data);
}

void AWarriorHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	WarriorsAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWarriorHeroCharacter::Input_AbilityInputRealesed(FGameplayTag InInputTag)
{
	WarriorsAbilitySystemComponent->OnAbilityInputRealesed(InInputTag);
}

// Called every frame
void AWarriorHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
