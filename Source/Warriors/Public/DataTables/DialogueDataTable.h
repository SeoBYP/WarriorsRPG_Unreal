// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueDataTable.generated.h"

// 대화 유형을 정의하는 열거형
UENUM(BlueprintType, meta = (ScriptName="DialogueType"))
enum class EDialogueType : uint8
{
	EDT_InformationOnly UMETA(DisplayName = "InformationOnly"), // 정보 제공만 하는 대화
	EDT_QuestAvailable UMETA(DisplayName = "QuestAvailable"), // 퀘스트를 받을 수 있는 대화
	EDT_QuestInProgress UMETA(DisplayName = "QuestInProgress"), // 진행 중인 퀘스트 관련 대화
	EDT_QuestCompleted UMETA(DisplayName = "QuestCompleted"), // 완료된 퀘스트 관련 대화
	EDT_QuestFinished UMETA(DisplayName = "QuestFinished"), // 퀘스트가 완전히 끝난 대화
	EDT_QuestFailed UMETA(DisplayName = "QuestFailed"), // 실패한 퀘스트 관련 대화
	EDT_Trader UMETA(DisplayName = "Trader"), // 상인과의 대화
	EDT_Combatant UMETA(DisplayName = "Combatant"), // 전투 관련 대화
	EDT_Follower UMETA(DisplayName = "Follower"), // 동료와의 대화

	EDT_MAX UMETA(DisplayName = "Default_MAX"), // MAX 값
};

// 대화 데이터 테이블 구조체
USTRUCT(BlueprintType)
struct FDialogueDataTable : public FTableRowBase
{
	GENERATED_BODY()

	// 대화의 고유 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue Properties")
	FString DialogueID = "UNSET";

	// 관련된 NPC의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue Properties")
	FString NPCID = "UNSET";

	// 대화의 유형 (정보 제공, 퀘스트 등)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue Properties")
	EDialogueType DialogueType;

	// 관련 퀘스트의 ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue Properties")
	FString RelatedQuestID;

	// 대화 시작에 필요한 캐릭터의 최소 레벨
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue Properties")
	int32 PrerequisiteCharacterLevel;

	// 대화를 반복할 수 있는지 여부
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Dialogue Properties")
	bool bIsRepeatable;

	// DialogueDataTable.h 또는 FDialogueDataTable이 정의된 헤더 파일
	FORCEINLINE bool operator==(const FDialogueDataTable& Other) const
	{
		return DialogueID == Other.DialogueID &&
			NPCID == Other.NPCID &&
			DialogueType == Other.DialogueType &&
			RelatedQuestID == Other.RelatedQuestID &&
			PrerequisiteCharacterLevel == Other.PrerequisiteCharacterLevel &&
			bIsRepeatable == Other.bIsRepeatable;
	}
};
