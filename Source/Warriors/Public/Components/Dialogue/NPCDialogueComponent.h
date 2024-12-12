// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "DataTables/DialogueDataTable.h"
#include "DataTables/DialogueResponseDataTable.h"
#include "DataTables/DialogueStepDataTable.h"
#include "NPCDialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartDialogueDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDialogueDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDisplayDialogueDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckResponseDelegate,FString,Response);

UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UNPCDialogueComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue",meta=(AllowPrivateAccess="true"))
	FDialogueDataTable CurrentDialogueData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue",meta=(AllowPrivateAccess="true"))
	FDialogueStepDataTable CurrentDialogueStepData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue",meta=(AllowPrivateAccess="true"))
	int32 CurrentDialogueStepIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue",meta=(AllowPrivateAccess="true"))
	TArray<FDialogueDataTable> CompletedDialogues;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue",meta=(AllowPrivateAccess="true"))
	FDialogueStepDataTable LastDialogueStep;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialogue",meta=(AllowPrivateAccess="true"))
	FDialogueResponseDataTable LastPlayerResponse;
	
	UPROPERTY(BlueprintAssignable,BlueprintCallable,meta=(AllowPrivateAccess="true"))
	FStartDialogueDelegate OnStartDialogue;

	UPROPERTY(BlueprintAssignable,BlueprintCallable,meta=(AllowPrivateAccess="true"))
	FEndDialogueDelegate OnEndDialogue;

	UPROPERTY(BlueprintAssignable,BlueprintCallable,meta=(AllowPrivateAccess="true"))
	FDisplayDialogueDelegate OnDisplayDialogue;

	UPROPERTY(BlueprintAssignable,BlueprintCallable,meta=(AllowPrivateAccess="true"))
	FCheckResponseDelegate OnCheckResponse;
	
public:
	UFUNCTION(BlueprintCallable)
	FDialogueDataTable GetDialogueDataTable();

	UFUNCTION(BlueprintCallable)
	EDialogueType GetDialogueType();
};
