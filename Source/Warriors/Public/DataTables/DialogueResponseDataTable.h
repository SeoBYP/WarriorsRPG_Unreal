// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueResponseDataTable.generated.h"

// 대화 응답의 텍스트 색상 유형을 정의하는 열거형
UENUM(BlueprintType, meta = (ScriptName="DialogueResponseColorType"))
enum class EDialogueResponseColorType : uint8
{
	EDC_White UMETA(DisplayName = "White"),
	EDC_Orange UMETA(DisplayName = "Orange"),
	EDC_Red UMETA(DisplayName = "Red"),
	EDC_Yellow UMETA(DisplayName = "Yellow"),
};

// 카리스마 체크 실패 시 응답 유형을 정의하는 열거형
UENUM(BlueprintType, meta = (ScriptName="CharismaCheckFailureResponseEnum"))
enum class ECharismaCheckFailureResponseEnum : uint8
{
	ECF_DoNothing UMETA(DisplayName = "DoNothing"),
	ECF_Flee UMETA(DisplayName = "Flee"),
	ECF_Attack UMETA(DisplayName = "Attack"),
};

// 대화 응답 데이터 테이블의 구조체
USTRUCT(BlueprintType)
struct FDialogueResponseDataTable : public FTableRowBase
{
	GENERATED_BODY()

	// 이 대화 응답의 고유 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	FString DialogueResponseID = "UNSET";

	// 관련 NPC 대화 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	FString NPCDialogueStepID = "UNSET";

	// 대화 시 출력되는 음성 큐
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	TSubclassOf<USoundCue> SpokenSentence;

	// 대화의 텍스트 문장
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	FText WrittenSentence;

	// 이 응답이 대화를 끝내는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	bool CausesDialogueToEnd;
	
	// 이 응답이 퀘스트를 시작하는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	bool StartsQuest;

	// 이 응답이 퀘스트를 완료하는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	bool FinishesQuest;

	// 관련된 퀘스트의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	FString QuestID = "UNSET";

	// 대화 응답 텍스트의 색상
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	EDialogueResponseColorType TextColour;

	// 관련된 NPC의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DialogueResponse Properties")
	FString NPCID = "UNSET";
};
