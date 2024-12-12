// Vince Petrelli All Rights Reserved


#include "Systems/DialogueSubSystem.h"

#include "VectorVMCommon.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Components/Quest/QuestLogComponent.h"

void UDialogueSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadDialogueDataTable();
	LoadDialogueResponseDataTable();
	LoadDialogueStepDataTable();
}

void UDialogueSubSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UDialogueSubSystem::LoadDialogueDataTable()
{
	DialogueDataTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(), nullptr,
		                 TEXT(
			                 "/Script/Engine.DataTable'/Game/DataTables/Dialogue/DT_DialogueDataTable.DT_DialogueDataTable'")));
	DialogueDataArray.Empty();
	if (DialogueDataTable)
	{
		TArray<FDialogueDataTable*> RowArray;
		DialogueDataTable->GetAllRows<FDialogueDataTable>(TEXT("Can't Find FDialogueDataTable Rows"),
		                                                  RowArray);
		for (FDialogueDataTable* Row : RowArray)
		{
			DialogueDataArray.Add(*Row);
		}
		UE_LOG(LogTemp, Log, TEXT("DialogueDataTable loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueDataTable could not be loaded."));
	}
}

void UDialogueSubSystem::LoadDialogueStepDataTable()
{
	DialogueStepDataTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(), nullptr,
		                 TEXT(
			                 "/Script/Engine.DataTable'/Game/DataTables/Dialogue/DT_DialogueStepDataTable.DT_DialogueStepDataTable'")));
	DialogueStepDataArray.Empty();
	if (DialogueStepDataTable)
	{
		TArray<FDialogueStepDataTable*> RowArray;
		DialogueStepDataTable->GetAllRows<FDialogueStepDataTable>(TEXT("Can't Find FDialogueDataTable Rows"),
		                                                          RowArray);
		for (FDialogueStepDataTable* Row : RowArray)
		{
			DialogueStepDataArray.Add(*Row);
		}
		UE_LOG(LogTemp, Log, TEXT("DialogueStepDataTable loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueStepDataTable could not be loaded."));
	}
}

void UDialogueSubSystem::LoadDialogueResponseDataTable()
{
	DialogueResponseDataTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(), nullptr,
		                 TEXT(
			                 "/Script/Engine.DataTable'/Game/DataTables/Dialogue/DT_DialogueResponseDataTable.DT_DialogueResponseDataTable'")));
	DialogueResponseDataArray.Empty();
	if (DialogueResponseDataTable)
	{
		TArray<FDialogueResponseDataTable*> RowArray;
		DialogueResponseDataTable->GetAllRows<FDialogueResponseDataTable>(TEXT("Can't Find FDialogueDataTable Rows"),
		                                                                  RowArray);
		for (FDialogueResponseDataTable* Row : RowArray)
		{
			DialogueResponseDataArray.Add(*Row);
		}
		UE_LOG(LogTemp, Log, TEXT("DialogueResponseDataTable loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueResponseDataTable could not be loaded."));
	}
}

bool UDialogueSubSystem::IsQuestFailedDialogue() const
{
	bool IsQuestFailedType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_QuestFailed;
	bool isFailed = CachedQuestLogComponent->IsQuestFailed(CachedLocalDialogue.RelatedQuestID) ||
		CachedLocalDialogue.bIsRepeatable;
	bool isCompletedDialogue = CachedCompletedDialogues.Contains(CachedLocalDialogue);
	return IsQuestFailedType && isFailed && !isCompletedDialogue;
}

bool UDialogueSubSystem::IsQuestFinishedDialogue()
{
	bool IsQuestFinishedType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_QuestFinished;
	bool isFinished = CachedQuestLogComponent->IsQuestFinished(CachedLocalDialogue.RelatedQuestID) ||
		CachedLocalDialogue.bIsRepeatable;
	bool isCompletedDialogue = CachedCompletedDialogues.Contains(CachedLocalDialogue);
	return IsQuestFinishedType && isFinished && !isCompletedDialogue;
}

bool UDialogueSubSystem::IsQuestCompletedDialogue()
{
	bool IsQuestCompletedType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_QuestCompleted;
	bool isCompleted = CachedQuestLogComponent->IsQuestCompleted(CachedLocalDialogue.RelatedQuestID) ||
		CachedLocalDialogue.bIsRepeatable;
	bool isCompletedDialogue = CachedCompletedDialogues.Contains(CachedLocalDialogue);
	return IsQuestCompletedType && isCompleted && !isCompletedDialogue;
}

bool UDialogueSubSystem::IsQuestProgressDialogue()
{
	bool IsQuestProgressType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_QuestInProgress;
	bool isProgress = CachedQuestLogComponent->IsQuestStarted(CachedLocalDialogue.RelatedQuestID) ||
		CachedLocalDialogue.bIsRepeatable;
	bool isCompletedDialogue = CachedCompletedDialogues.Contains(CachedLocalDialogue);
	return IsQuestProgressType && isProgress && !isCompletedDialogue;
}

bool UDialogueSubSystem::IsQuestAvailableDialogue()
{
	bool IsQuestAvailableType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_QuestAvailable;
	bool isFailed = CachedQuestLogComponent->IsQuestFailed(CachedLocalDialogue.RelatedQuestID);
	bool isFinished = CachedQuestLogComponent->IsQuestFinished(CachedLocalDialogue.RelatedQuestID);
	bool isCompleted = CachedQuestLogComponent->IsQuestCompleted(CachedLocalDialogue.RelatedQuestID);
	bool isProgress = CachedQuestLogComponent->IsQuestStarted(CachedLocalDialogue.RelatedQuestID);
	return !IsQuestAvailableType && (!isFailed && !isFinished && !isCompleted && !isProgress);
}

bool UDialogueSubSystem::IsFollowerDialogue()
{
	bool IsFolloweType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_Follower;
	bool isCompletedDialogue = CachedCompletedDialogues.Contains(CachedLocalDialogue);
	return IsFolloweType && (!isCompletedDialogue || CachedLocalDialogue.bIsRepeatable);
}

bool UDialogueSubSystem::IsOtherDialogue()
{
	bool IsOtherType = CachedLocalDialogue.DialogueType == EDialogueType::EDT_Trader ||
		CachedLocalDialogue.DialogueType == EDialogueType::EDT_InformationOnly;
	bool isCompletedDialogue = CachedCompletedDialogues.Contains(CachedLocalDialogue);
	return IsOtherType && (!isCompletedDialogue || CachedLocalDialogue.bIsRepeatable);
}

FDialogueStepDataTable UDialogueSubSystem::GetStepDataTableByIndex(FString DialogueID, int32 Index)
{
	TArray<FDialogueStepDataTable*> Steps;
	TArray<FDialogueStepDataTable> QueriedSteps;
	DialogueStepDataTable->GetAllRows(TEXT("Can't find steps for DialogueID"), Steps);
	for (FDialogueStepDataTable* Step : Steps)
	{
		if (Step->DialogueID != DialogueID) continue;
		QueriedSteps.Add(*Step);
	}
	if (!QueriedSteps.IsEmpty() && QueriedSteps.IsValidIndex(Index))
		return QueriedSteps[Index];
	return FDialogueStepDataTable();
}

FDialogueStepDataTable UDialogueSubSystem::GetStepDataTableByPrerequisite(
	FString DialogueID, FString PrerequisiteResponseID)
{
	TArray<FDialogueStepDataTable*> Steps;
	TArray<FDialogueStepDataTable> QueriedSteps;
	DialogueStepDataTable->GetAllRows(TEXT("Can't find steps for DialogueID"), Steps);
	for (FDialogueStepDataTable* Step : Steps)
	{
		if (Step->DialogueID != DialogueID) continue;
		if (Step->PrerequisiteResponseID == PrerequisiteResponseID)
			return *Step;
	}
	return FDialogueStepDataTable();
}

FDialogueDataTable UDialogueSubSystem::GetDialogueByNPC(FNPCDataTable NPC,
                                                        TArray<FDialogueDataTable> CompletedDialogues)
{
	AWarriorHeroCharacter* HeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld());
	if (HeroCharacter == nullptr) return FDialogueDataTable();
	CachedQuestLogComponent = HeroCharacter->GetQuestLogComponent();
	if (CachedQuestLogComponent == nullptr) return FDialogueDataTable();
	CachedNPC = NPC;
	CachedCompletedDialogues = CompletedDialogues;
	Debug::Log(
		FString::Printf(TEXT("[GetDialogueByNPC] BEGIN : NPC ID == %s,NPC Name == %s"), *NPC.ID, *NPC.Name.ToString()));
	for (FDialogueDataTable LocalDialogue : DialogueDataArray)
	{
		Debug::Log(
			FString::Printf(TEXT("[GetDialogueByNPC] LocalWorldDialogue->NPCID == %s"), *LocalDialogue.NPCID));
		CachedLocalDialogue = LocalDialogue;
		bool isSameNPC = CachedNPC.ID == CachedLocalDialogue.NPCID;
		if (!isSameNPC) continue;

		if (IsQuestFailedDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
		if (IsQuestFinishedDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
		if (IsQuestCompletedDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
		if (IsQuestProgressDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
		if (IsQuestAvailableDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
		if (IsFollowerDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
		if (IsOtherDialogue())
		{
			Debug::Log(FString::Printf(
				TEXT("[GetDialogueByNPC] Found dialogue for this NPC, DialogueID == %s"),
				*CachedLocalDialogue.DialogueID));
			return LocalDialogue;
		}
	}

	Debug::Log(FString::Printf(TEXT("[GetDialogueByNPC] Found no relevant dialogue")));
	return FDialogueDataTable();
}

FDialogueStepDataTable UDialogueSubSystem::GetDialogueStepByDialogueAndResponse(FDialogueDataTable Dialogue,
	FDialogueResponseDataTable Response, bool CharismaCheckSucceeded)
{
	FString DebugText = FString::Printf(
		TEXT("[Get Dialogue Step by Dialogue and Response] Params : Dialogue->DialogueID == %s, "
			"Dialogue->NPCID == %s, "
			"Response->DialogueResponseID == %s, "
			"CharismaCheckSucceeded == %d"),
		*Dialogue.DialogueID,
		*Dialogue.NPCID,
		*Response.DialogueResponseID,
		CharismaCheckSucceeded ? 1 : 0 // bool 값을 int로 변환
	);
	Debug::Log(DebugText);

	FDialogueStepDataTable LocalDialogueStep = FDialogueStepDataTable();
	for (FDialogueStepDataTable Step : DialogueStepDataArray)
	{
		bool isSameDialogueID = Dialogue.DialogueID == Step.DialogueID;
		bool isRequireResponse = Response.DialogueResponseID == Step.PrerequisiteResponseID;
		if (isSameDialogueID && isRequireResponse)
		{
			LocalDialogueStep = Step;
			break;
		}
	}

	DebugText = FString::Printf(
				TEXT(
					"[Get Dialogue Step by Dialogue and Response] Found relevant Dialogue Step : DialogueStepID == %s, "
					"WrittenSentence ==  %s, "
					"CausesDialogueToEnd == %d"),
				*LocalDialogueStep.DialogueStepID,
				*LocalDialogueStep.WrittenSentence.ToString(),
				LocalDialogueStep.CausesDialogueToEnd ? 1 : 0 // bool 값을 int로 변환
			);
	Debug::Log(DebugText);
	
	return LocalDialogueStep;
}

FDialogueStepDataTable UDialogueSubSystem::GetDialogueStepbyDialogueandPreviousDialogueStep(
	FDialogueDataTable Dialogue, FDialogueStepDataTable PreviousDialogueStep)
{
	FString DebugText = FString::Printf(
			TEXT(
				"[Get Dialogue Step by Dialogue and Previous Dialogue Step] Params : Dialogue->DialogueID == %s"
				", Dialogue->NPCID == %s"
				", PreviousDialogueStep->DialogueStepID == %s"),
			*Dialogue.DialogueID,
			*Dialogue.NPCID,
			*PreviousDialogueStep.DialogueStepID);
	FDialogueStepDataTable LocalDialogueStep = FDialogueStepDataTable();
	bool LocalFoundPreviousDialogueStep= false;
	for (FDialogueStepDataTable Step : DialogueStepDataArray)
	{
		if(LocalFoundPreviousDialogueStep)
		{
			bool IsSame = Dialogue.DialogueID == Step.DialogueID;
			if(IsSame)
			{
				LocalDialogueStep = Step;
				break;
			}
		}
		bool isSameDialogueID = Dialogue.DialogueID == PreviousDialogueStep.DialogueID;
		bool isSameStepDialogueID = Step.DialogueStepID == PreviousDialogueStep.DialogueStepID;
		if (isSameDialogueID && isSameStepDialogueID)
		{
			LocalFoundPreviousDialogueStep = true;
		}
	}
	DebugText = FString::Printf(
				TEXT(
					"[Get Dialogue Step by Dialogue and Previous Dialog] Found relevant Dialogue Step : DialogueStepID ==  %s"
					", WrittenSentence == %s"),
				*LocalDialogueStep.DialogueStepID,
				*LocalDialogueStep.WrittenSentence.ToString());
	return LocalDialogueStep;
}

TArray<FDialogueResponseDataTable> UDialogueSubSystem::GetAvailableDialogueResponses(
	FDialogueStepDataTable DialogueStep, bool IsNPCFollowingPlayer)
{
	TArray<FDialogueResponseDataTable> LocalDialogueResponses;

	AWarriorHeroCharacter* HeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld());
	if (HeroCharacter == nullptr) return LocalDialogueResponses;
	CachedQuestLogComponent = HeroCharacter->GetQuestLogComponent();
	if (CachedQuestLogComponent == nullptr) return LocalDialogueResponses;
	
	for (FDialogueResponseDataTable Response : DialogueResponseDataArray)
	{
		bool isSameDialogueStepID = DialogueStep.DialogueStepID == Response.NPCDialogueStepID;
		bool isQuestFinished = (!Response.FinishesQuest ||
			(Response.FinishesQuest && CachedQuestLogComponent->IsQuestCompleted(Response.QuestID)));
		// TODO : 플레이어가 NPC에게 돈을 줘야 하는 지 한다면 해당 부분을 체크합니다.
		// TODO : 해당 답변이 플레이어를 따라다녀야 하는 답변이라면 NPC가 플레이어를 현재 따라다니고 있는 상태인지 확인
		// TODO : 해당 답변이 플레이어를 그만 따라다녀야 하는 답변이라면 NPC가 플레이어를 현재 따라다니고 있는 상태인지 확인
		if(isSameDialogueStepID && isQuestFinished)
		{
			LocalDialogueResponses.Add(Response);
		}
	}
	return LocalDialogueResponses;
}
