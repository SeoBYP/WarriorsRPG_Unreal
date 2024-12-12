// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DialogueResponseButtonWidget.h"
#include "Characters/NPC/WarriorNPCCharacter.h"
#include "DataTables/DialogueDataTable.h"
#include "DataTables/DialogueResponseDataTable.h"
#include "DataTables/DialogueStepDataTable.h"
#include "DataTables/NPCDataTable.h"
#include "Widgets/WarriorWidgetBase.h"
#include "DialogueOverlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UDialogueOverlayWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	FString DialogueCurrentText;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	FString DialogueFullText;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	AWarriorNPCCharacter* NPCActor;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	FNPCDataTable CurrentNPCInfo;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	UAudioComponent* NPCAudio;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	FDialogueDataTable CurrentDialogue;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	FDialogueStepDataTable CurrentDialogueStep;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	FDialogueResponseDataTable PlayersResponse;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	TArray<FDialogueResponseDataTable> AvailableDialogueResponses;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	TArray<UDialogueResponseButtonWidget*>NavigationDialogueResponsesArray;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	int32 NavigationIndex;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	bool PlayingNPCSpeech;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Dialogue",meta=(AllowPrivateAccess=true))
	bool SpeechInterrupted;
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void BeginDialogue(FNPCDataTable NPCInfo, UAudioComponent* InNPCAudio,
		AWarriorNPCCharacter* NPC, const TArray<FDialogueDataTable>& NPCCompletedDialogues);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void WaitUntilEndOfSpeech();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool IsCanShowPlayerResponse(AWarriorNPCCharacter* InNPC);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ShowPlayerResponses(AWarriorNPCCharacter* InNPC);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ProcessResponse(FDialogueResponseDataTable Response);

public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void UpdateNavigationAppearance();
};
