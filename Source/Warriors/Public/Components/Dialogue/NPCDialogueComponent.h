// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnDialogueComponent.h"
#include "NPCDialogueComponent.generated.h"



UENUM(BlueprintType,BlueprintType)
enum class EWarriorDialogueType : uint8
{
	None,
	BehaviorTree,
	NonBehaviorTree,
};

UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UNPCDialogueComponent : public UPawnDialogueComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void StartDialogue();

	UFUNCTION(BlueprintCallable)
	void EndDialogue();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue",meta = (AllowPrivateAccess = "True"))
	EWarriorDialogueType DialogueType = EWarriorDialogueType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue",
		meta=(AllowPrivateAccess = "True",EditCondition = "DialogueType == EWarriorDialogueType::NonBehaviorTree"))
	FString DialogueText = "";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue",
		meta=(AllowPrivateAccess = "True", EditCondition = "DialogueType == EWarriorDialogueType::NonBehaviorTree"))
	FString Speaker = "";
	
};
