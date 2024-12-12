// Vince Petrelli All Rights Reserved


#include "Components/Dialogue/HeroDialogueComponent.h"
#include "WarriorDebugHelper.h"
#include "Camera/CameraComponent.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Components/UI/HeroUIComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DialogueInterface.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetSystemLibrary.h"

// void UHeroDialogueComponent::DialogueInteractCheck(UCameraComponent* FollowCamera)
// {
// 	if(!ensure(FollowCamera)) Debug::LogWarning(TEXT("Follow Camera Is Null"));
// 	
// 	APawn* OwnerPawn = GetOwningPawn();
//
// 	if(!ensure(OwnerPawn)) Debug::LogWarning(TEXT("Owner Pawn Is Null"));
//
// 	const UWorld* World = GetWorld();
// 	if(!World)
// 	{
// 		Debug::LogWarning(TEXT("World Is Null"));
// 		return;
// 	}
//
// 	FVector StartLocation = OwnerPawn->GetActorLocation();
// 	FVector EndLocation = (FollowCamera->GetForwardVector() * 200.0f) + StartLocation;
//
// 	TArray<AActor*> ActorsToIgnore;
// 	ActorsToIgnore.Add(GetOwningPawn());
// 	TArray<FHitResult> HitResults;
// 	
// 	const bool bBlockingHit = UKismetSystemLibrary::SphereTraceMulti(
// 		World,
// 		StartLocation,
// 		EndLocation,
// 		Radius,
// 		UEngineTypes::ConvertToTraceType(ECC_Camera),
// 		false,
// 		ActorsToIgnore,
// 		EDrawDebugTrace::None,
// 		HitResults,
// 		true,
// 		FLinearColor::Red,
// 		FLinearColor::Green,
// 		5.0f
// 		);
//
// 	bool bInteracted = false;
//
// 	if(bBlockingHit)
// 	{
// 		for(FHitResult HitResult :  HitResults)
// 		{
// 			AActor* HitActor = HitResult.GetActor();
// 			if (HitActor && HitActor->GetClass()->ImplementsInterface(UDialogueInterface::StaticClass()))
// 			{
// 				if (IDialogueInterface* DialogueInterface = Cast<IDialogueInterface>(HitActor))
// 				{
// 					InteractedActor = HitActor;
// 					bInteracted = true;
// 				}
// 			}
// 		}
// 	}
// 	//Debug::DebugLog(bInteracted ? FString::Printf(TEXT("Have Interacted Actor : %s"),*InteractedActor->GetName()) : TEXT("No Interacted Actor"));
// 	ShowInteractDisplay(bInteracted);
// }
//
// void UHeroDialogueComponent::ShowInteractDisplay(bool interacted) const
// {
// 	APawn* OwnerPawn = GetOwningPawn();
//
// 	if(!ensure(OwnerPawn)) Debug::LogWarning(TEXT("Owner Pawn Is Null"));
//
// 	if(AWarriorHeroCharacter* HeroCharacter = Cast<AWarriorHeroCharacter>(OwnerPawn))
// 	{
// 		//HeroCharacter->GetHeroUIComponent()->OnDisplayInteracted.Broadcast(InteractedActor, interacted);
// 	}
// }
//
// void UHeroDialogueComponent::RequestDialogue()
// {
// 	if(!ensure(InteractedActor))
// 		Debug::LogWarning(TEXT("InteractedActor Is Null"));
//
// 	if (IDialogueInterface* DialogueInterface = Cast<IDialogueInterface>(InteractedActor))
// 	{
// 		// Execute_를 사용하여 인터페이스 함수 호출
// 		IDialogueInterface::Execute_OnRequestStartDialogue(InteractedActor);
// 	}
// }