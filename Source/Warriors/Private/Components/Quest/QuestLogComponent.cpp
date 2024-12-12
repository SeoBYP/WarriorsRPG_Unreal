// Vince Petrelli All Rights Reserved


#include "Components/Quest/QuestLogComponent.h"

#include "WarriorDebugHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestBase.h"
#include "Systems/SaveLoadSubSystem.h"
#include "Systems/WidgetSubSystem.h"

void UQuestLogComponent::SaveQuestData()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	if(!ensure(GameInstance))
	{
		Debug::LogWarning("GameInstance is null");
		return;
	}
	USaveLoadSubSystem* SaveLoadSubSystem = GameInstance->GetSubsystem<USaveLoadSubSystem>();
	if(!ensure(SaveLoadSubSystem))
	{
		Debug::LogWarning("SaveLoadSubSystem is null");
		return;
	}

	for(AQuestBase* Quest : CurrentQuests){
		SaveLoadSubSystem->SaveQuestDetails(Quest);
	}
	SaveLoadSubSystem->SaveQuestLog(this);
	SaveLoadSubSystem->SaveQuestSaveData();
}

AQuestBase* UQuestLogComponent::AddNewQuest(FName QuestID)
{
	CurrentActiveQuests.AddUnique(QuestID);
	if (GetWorld())
	{
		// Spawn parameters 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// AQuestBase 액터를 지연 스폰
		AQuestBase* NewQuestActor = GetWorld()->SpawnActorDeferred<AQuestBase>
			(AQuestBase::StaticClass(), FTransform(FVector::ZeroVector),
				nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (NewQuestActor)
		{
			// 스폰된 Quest 액터에 QuestID를 설정하거나 초기화 작업 수행
			NewQuestActor->SetQuestID(QuestID);
			
			// FinishSpawning을 호출하여 스폰 완료
			NewQuestActor->FinishSpawning(FTransform(FVector::ZeroVector));
			
			CurrentQuests.Add(NewQuestActor);
			UE_LOG(LogTemp, Log, TEXT("New Quest Actor created with ID: %s"), *QuestID.ToString());
			return NewQuestActor;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Quest Actor for Quest ID: %s"), *QuestID.ToString());
		}
	}
	return nullptr;
}

void UQuestLogComponent::CompleteQuest(FName QuestID)
{
	CompletedQuests.AddUnique(QuestID);
	CurrentActiveQuests.Remove(QuestID);
	if(AQuestBase* QuestBase = GetQuestActor(QuestID))
	{
		QuestBase->SetIsTurned(true);
		OnQuestCompleted.Broadcast(QuestBase);
	}
}
void UQuestLogComponent::TrackQuest(AQuestBase* QuestActor)
{
	//TODO : Widget 업데이트 로직
	if(UWidgetSubSystem* WidgetSubSystem = GetWorld()->GetSubsystem<UWidgetSubSystem>())
	{
		if(UQuestTrackerWidget* QuestTrackerWidget = WidgetSubSystem->GetQuestTrackerWidget())
		{
			QuestTrackerWidget->AddToViewport();
			QuestTrackerWidget->OnUpdateQuestTrackerWidget(QuestActor);
		}
	}
}

AQuestBase* UQuestLogComponent::GetQuestActor(FName QuestID)
{
	for (AQuestBase* Quest : CurrentQuests)
	{
		if(Quest->GetQuestID() == QuestID)
		{
			return Quest;
		}
	}
	return nullptr;
}

void UQuestLogComponent::TurnInQuest(FName QuestID)
{
	if(AQuestBase* QuestBase = GetQuestActor(QuestID))
	{
		Debug::Log(FString::Printf(TEXT("XP = %d"),QuestBase->GetCurrentStageDetails().XPReward));
		CompleteQuest(QuestID);
	}
}

bool UQuestLogComponent::QueryActiveQuest(FName QuestID)
{
	return CurrentActiveQuests.Contains(QuestID);
}

bool UQuestLogComponent::QueryCompletedQuests(FName QuestID, bool& TurnedIn)
{
	if(AQuestBase* Quest = GetQuestActor(QuestID))
	{
		TurnedIn = Quest->GetIsTurned(); 
	}
	else
	{
		TurnedIn = true;
	}
	
	return CompletedQuests.Contains(QuestID);
}
// TODO : Quest 실패 로직 구현
bool UQuestLogComponent::IsQuestFailed(FString QuestID)
{
	return false;
}

bool UQuestLogComponent::IsQuestFinished(FString QuestID)
{
	bool IsReturned = false;
	if(AQuestBase* Quest = GetQuestActor(FName(*QuestID))) IsReturned = Quest->GetIsTurned();
	else IsReturned = true;
	return IsReturned && CompletedQuests.Contains(QuestID);
}

bool UQuestLogComponent::IsQuestCompleted(FString QuestID)
{
	bool IsReturned = false;
	if(AQuestBase* Quest = GetQuestActor(FName(*QuestID))) IsReturned = Quest->GetIsTurned();
	else IsReturned = true;
	return !IsReturned && CompletedQuests.Contains(QuestID);
}

bool UQuestLogComponent::IsQuestStarted(FString QuestID)
{
	return CurrentActiveQuests.Contains(FName(*QuestID));
}
