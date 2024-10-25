// Vince Petrelli All Rights Reserved


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayEffectTypes.h"
#include "WarriorDebugHelper.h"
#include "AbilitySystem/WarriorsAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utils/WarriorGameplayTags.h"
#include "WarriorTypes/WarriorCountDownAction.h"
#include "WarriorGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/WarriorSaveGame.h"

UWarriorsAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UWarriorsAbilitySystemComponent>(
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));;
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UWarriorsAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
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

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
                                                  EWarriorConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::YES : EWarriorConfirmType::NO;
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFormActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFormActor(AActor* InActor,
	EWarriorVaildType& OutVaildType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFormActor(InActor);
	OutVaildType = CombatComponent ? EWarriorVaildType::Vaild : EWarriorVaildType::Invalid;
	return CombatComponent;
}

bool UWarriorFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UWarriorFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UWarriorFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictom,
                                                                  float& OutAngleDifference)
{
	check(InAttacker && InVictom);
	const FVector VictimForaward = InVictom->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictom->GetActorLocation()).
		GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForaward, VictimToAttackerNormalized);

	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForaward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.0f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return WarriorsGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return WarriorsGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return WarriorsGameplayTags::Shared_Status_HitReact_Back;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return WarriorsGameplayTags::Shared_Status_HitReact_Right;
	}
	return WarriorsGameplayTags::Shared_Status_HitReact_Front;
}

bool UWarriorFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(),
	                                            InDefender->GetActorForwardVector());

	const FString DebugString = FString::Printf(TEXT("Dot result %f %s"), DotResult,
	                                            DotResult < 0.f ? TEXT("valid Block") : TEXT("not valid Block"));

	return DotResult < -0.1f;
}

bool UWarriorFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor,
                                                                         const FGameplayEffectSpecHandle& InSpecHandle)
{
	UWarriorsAbilitySystemComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);
	UWarriorsAbilitySystemComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UWarriorFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
                                        float& OutRemainingTime, EWarriorCountDownActionInput CountDownInput,
                                        UPARAM(DisplayName = "Output") EWarriorCountDownActionOutput& CountDownOutput,
                                        FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;
	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}
	if (!World)
	{
		return;
	}

	//FLatentActionManager 에 대해서 문서화
	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FWarriorCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FWarriorCountDownAction>(
		LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == EWarriorCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FWarriorCountDownAction(TotalTime, UpdateInterval, OutRemainingTime,
				                            CountDownOutput, LatentInfo));
		}
	}

	if (CountDownInput == EWarriorCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UWarriorGameInstance* UWarriorFunctionLibrary::GetWarriorGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UWarriorGameInstance>();
		}
	}
	return nullptr;
}

void UWarriorFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EWarriorInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->
			GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}
	if (!PlayerController)
	{
		return;
	}

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnlyMode;
	switch (InInputMode)
	{
	case EWarriorInputMode::GameOnly:
		PlayerController->SetInputMode(GameOnlyMode);
		PlayerController->bShowMouseCursor = false;
		break;
	case EWarriorInputMode::UIOnly:
		PlayerController->SetInputMode(UIOnlyMode);
		PlayerController->bShowMouseCursor = true;
		break;
	default: ;
	}
}

void UWarriorFunctionLibrary::SaveCurrentGameDifficulty(EWarriorGameDifficulty InDifficultyToSave)
{
 	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UWarriorSaveGame::StaticClass());

	if(UWarriorSaveGame* WarriorSaveGameObject = Cast<UWarriorSaveGame>(SaveGameObject))
	{
		WarriorSaveGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

	 	const bool bWasSaved = UGameplayStatics::SaveGameToSlot(WarriorSaveGameObject,
			WarriorsGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(),
			0);

		Debug::DebugLog(bWasSaved ? TEXT("Difficulty Saved") : TEXT("Difficulty Not Saved"));
	}
}

bool UWarriorFunctionLibrary::TryLoadSavedGameDifficulty(EWarriorGameDifficulty& OutDifficultyToSave)
{
	if( UGameplayStatics::DoesSaveGameExist(WarriorsGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(),0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(WarriorsGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(),0);

		if(UWarriorSaveGame* WarriorSaveGameObject = Cast<UWarriorSaveGame>(SaveGameObject))
		{
			OutDifficultyToSave = WarriorSaveGameObject->SavedCurrentGameDifficulty;

			Debug::DebugLog(TEXT("Loading Successful"));
			return true;
		}
	}
	return false;
}

AWarriorHeroCharacter* UWarriorFunctionLibrary::GetWarriorHeroCharacter(const UObject* WorldContextObject)
{
	if(ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(WorldContextObject,0))
	{
		if(AWarriorHeroCharacter* WarriorHeroCharacter = Cast<AWarriorHeroCharacter>(PlayerCharacter))
		{
			return WarriorHeroCharacter;
		}
	}
	return nullptr;
}
