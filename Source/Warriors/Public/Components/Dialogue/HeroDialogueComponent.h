// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "HeroDialogueComponent.generated.h"


class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestStartSingleDialogueDelegate,FString,DialogueText,FString,Speaker);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRequestEndSingleDialogueDelegate);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UHeroDialogueComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
// public:
// 	UPROPERTY(BlueprintAssignable,BlueprintCallable)
// 	FOnRequestStartSingleDialogueDelegate OnStartDialogueDelegate;
//
// 	UPROPERTY(BlueprintAssignable,BlueprintCallable)
// 	FOnRequestEndSingleDialogueDelegate OnEndSingleDialogueDelegate;
// 	
// 	UFUNCTION(BlueprintCallable,Category="Dialogue")
// 	void DialogueInteractCheck(UCameraComponent* FollowCamera);
//
// 	UFUNCTION(BlueprintCallable,Category="Dialogue")
// 	void ShowInteractDisplay(bool interacted) const;
// 	
// 	UFUNCTION(BlueprintCallable,Category="Dialogue")
// 	void RequestDialogue();
//
// protected:
// 	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Dialogue")
// 	float Radius = 25.0f;
// 	
// 	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Dialogue")
// 	AActor* InteractedActor;
};
