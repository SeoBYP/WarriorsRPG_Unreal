// Vince Petrelli All Rights Reserved


#include "Quest/QuestBase.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Components/Quest/QuestLogComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "Systems/DataTableSubSystem.h"
#include "DataTables/QuestDataTable.h"
#include "Systems/QuestSubSystem.h"
#include "Systems/WidgetSubSystem.h"

// Sets default values
AQuestBase::AQuestBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AQuestBase::BeginPlay()
{
	Super::BeginPlay();

	// 현재 퀘스트 정보로 갱신
	GetQuestDetails();
	if(AWarriorHeroCharacter* WarriorHeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld()))
	{
		WarriorHeroCharacter->OnRequestObjectiveID.AddUniqueDynamic(this,&AQuestBase::OnObjectiveIDHeard);
		for(FObjectiveDetails Objective : CurrentStageDetails.Objectives)
		{
			if(Objective.Type != EObjectiveType::Collect) continue;
			int32 outValue = 0;
			bool success = false;
			WarriorHeroCharacter->GetInventoryComponent()->QueryInventory(FName(Objective.ObjectiveID),0,success,outValue);
			OnObjectiveIDHeard(Objective.ObjectiveID,outValue);
		}
		bIsCompleted = AreObjectivesComplete();
	}
}

void AQuestBase::OnObjectiveIDHeard(FString ObjectiveID, int32 Value)
{
	if(ObjectiveID.IsEmpty())
	{
		Debug::Log(FString::Printf(TEXT("[%s] ObjectiveID is Empty"), TEXT(__FUNCTION__)));
		return;
	}
	if (!(sin(Value) > 0))
	{
		int32* newValue = CurrentObjectiveProgress.Find(ObjectiveID);
		if (newValue) // 유효성 검사 추가
		{
			*newValue += Value;
			Debug::Log(FString::Printf(TEXT("[%s] Current Objective Progress : %s %i"), TEXT(__FUNCTION__), *ObjectiveID, *newValue));
		}
		return;
	}

	int32* newValue = CurrentObjectiveProgress.Find(ObjectiveID);
	if (newValue) // 유효성 검사 추가
	{
		if (*newValue < GetObjectiveDataByID(ObjectiveID).Quantity)
		{
			*newValue += Value;
			CheckObjectiveComplete(ObjectiveID);
			OnQuestObjectiveUpdated.Broadcast();
			if(AWarriorHeroCharacter* HeroCharacter =
				UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld()))
			{
				HeroCharacter->GetQuestLogComponent()->SaveQuestData();
			}
			Debug::Log(FString::Printf(TEXT("[%s] Current Objective Progress : %s %i"), TEXT(__FUNCTION__), *ObjectiveID, *newValue));
		}
		else
		{
			Debug::Log(FString::Printf(TEXT("[%s] %s : %d / %d"), TEXT(__FUNCTION__), *ObjectiveID, *newValue, GetObjectiveDataByID(ObjectiveID).Quantity));
		}
	}
	else
	{
		Debug::Log(FString::Printf(TEXT("[%s] %s can't Find Current Objective Progress"), TEXT(__FUNCTION__), *ObjectiveID));
	}


}
void AQuestBase::GetQuestDetails()
{
	UQuestSubSystem* QuestSubSystem = GetWorld()->GetSubsystem<UQuestSubSystem>();
	if(!ensure(QuestSubSystem))
	{
		Debug::LogWarning(FString::Printf(TEXT("[%s] Data Table SubSystem Is Null"), TEXT(__FUNCTION__)));
		return;
	}
	UDataTable* QuestDataTable = QuestSubSystem->GetQuestDataTable();
	if(!ensure(QuestDataTable))
	{
		Debug::LogWarning(FString::Printf(TEXT("[%s] Quest Data Table Is Null"), TEXT(__FUNCTION__)));
		return;
	}
	FQuestDataTable* DataTable = QuestDataTable->FindRow<FQuestDataTable>(
		QuestID, FString::Printf(TEXT("%s can't find Quest Data Table"), *QuestID.ToString()));
	if(DataTable)
	{
		QuestDetails = *DataTable;
		if(!QuestDetails.Stages.IsValidIndex(CurrentStage))
		{
			Debug::LogWarning(FString::Printf(TEXT("[%s] Quest Data Table Is Invalid Index"), TEXT(__FUNCTION__)));
			return;
		}
		CurrentStageDetails = QuestDetails.Stages[CurrentStage];
		CurrentObjectiveProgress.Empty();
		for(FObjectiveDetails Objective : CurrentStageDetails.Objectives)
		{
			CurrentObjectiveProgress.Add(Objective.ObjectiveID, 0);
		}
	}
}

FObjectiveDetails AQuestBase::GetObjectiveDataByID(FString ObjectiveID)
{
	for(FObjectiveDetails Objective : CurrentStageDetails.Objectives)
	{
		if(ObjectiveID == Objective.ObjectiveID)
		{
			return Objective;
		}
	}
	return FObjectiveDetails();
}
void AQuestBase::CheckObjectiveComplete(FString ObjectiveID)
{
	int32* progressValue = CurrentObjectiveProgress.Find(ObjectiveID);
	if(*progressValue < GetObjectiveDataByID(ObjectiveID).Quantity)
	{
		Debug::Log(FString::Printf(TEXT("[%s] %s still Continue Progress"), TEXT(__FUNCTION__), *ObjectiveID));
		return;
	}
	// 퀘스트 조건 클리어 알림 팝업 생성
	if(AWarriorHeroCharacter* HeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld()))
	{
		HeroCharacter->GetHeroUIComponent()->
			OnDisplayQuestObjectiveClearNotificationDelegate.Broadcast(FText::FromString(ObjectiveID));
	}
	if(AreObjectivesComplete())
	{
		CurrentStage++;
		if(QuestDetails.Stages.IsValidIndex(CurrentStage))
		{
			GetQuestDetails();
		}
		else
		{
			bIsCompleted = true;
			if(!QuestDetails.bAutoComplete)
			{
				Debug::Log(FString::Printf(TEXT("[%s] %s Complete"), TEXT(__FUNCTION__), *QuestID.ToString()));
				return;
			}
			if(AWarriorHeroCharacter* WarriorHeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld()))
			{
				WarriorHeroCharacter->GetQuestLogComponent()->TurnInQuest(QuestID);
				Debug::Log(FString::Printf(TEXT("[%s] %s Auto Complete"), TEXT(__FUNCTION__), *QuestID.ToString()));
			}
		}
	}
}
bool AQuestBase::AreObjectivesComplete()
{
	for(FObjectiveDetails Objective : CurrentStageDetails.Objectives)
	{
		int32* progressValue = CurrentObjectiveProgress.Find(Objective.ObjectiveID);
		int32 maxValue = GetObjectiveDataByID(Objective.ObjectiveID).Quantity;
		if(*progressValue < maxValue)
		{
			return false;
		}
	}
	return true;
}
