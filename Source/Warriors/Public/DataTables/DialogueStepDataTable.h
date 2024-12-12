// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueStepDataTable.generated.h"

// 대화 단계의 속성을 정의하는 데이터 테이블 구조체
USTRUCT(BlueprintType)
struct FDialogueStepDataTable : public FTableRowBase
{
	GENERATED_BODY()

	// 대화 단계의 고유 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	FString DialogueStepID = "UNSET";

	// 관련된 대화의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	FString DialogueID = "UNSET";

	// 대화 단계에 필요한 이전 응답의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	FString PrerequisiteResponseID = "UNSET";

	// 대화 단계에서 출력되는 음성 큐
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	TSubclassOf<USoundCue> SpokenSentence;

	// 대화 단계의 텍스트 문장
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	FText WrittenSentence;

	// 이 단계가 대화를 끝내는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	bool CausesDialogueToEnd;

	// 대화 단계의 지속 시간 (초 단위)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	float StepDuration;

	// 이 단계에서 퀘스트를 시작하는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	bool StartsQuest;

	// 이 단계에서 퀘스트를 완료하는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	bool FinishesQuest;

	// 관련된 퀘스트의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	FString QuestID;

	// 관련된 NPC의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueStep Properties")
	FString NPCID = "UNSET";
};
