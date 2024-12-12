// Vince Petrelli All Rights Reserved


#include "Systems/SaveLoadSubSystem.h"

#include "WarriorDebugHelper.h"
#include "Components/Quest/QuestLogComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestBase.h"

void USaveLoadSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TryLoadAllSaveData();
	Debug::Log(TEXT("SaveLoadSubSystem Initialized"));
}

void USaveLoadSubSystem::Deinitialize()
{
	Super::Deinitialize();
	SaveAllSaveData();
	Debug::Log(TEXT("SaveLoadSubSystem Reinitialized"));
}

void USaveLoadSubSystem::TryLoadAllSaveData()
{
	TryLoadInventorySaveData();
	TryLoadLevelSaveData();
	TryLoadQuestSaveData();
}

void USaveLoadSubSystem::SaveQuestDetails(AQuestBase* Quest)
{
	if(!ensure(Quest)) return;
	if(!ensure(QuestSaveData)) return;

	FQuestSaveDataConfig Config;
	Config.QuestProgress = Quest->GetCurrentObjectiveProgress();
	Config.CurrentStage = Quest->GetCurrentStage();

	QuestSaveData->QuestProgress.Add(Quest->GetQuestID(),Config);
}

void USaveLoadSubSystem::LoadQuests(UQuestLogComponent* InQuestLogComponent)
{
	if(!ensure(InQuestLogComponent)) return;
	if(!ensure(QuestSaveData)) return;

	for (FName ActiveQuestName : QuestSaveData->ActivedQuests)
	{
		AQuestBase* QuestBase = InQuestLogComponent->AddNewQuest(ActiveQuestName);
		if(FQuestSaveDataConfig* Config = QuestSaveData->QuestProgress.Find(ActiveQuestName))
		{
			QuestBase->SetCurrentStage(Config->CurrentStage);
			QuestBase->SetCurrentObjectiveProgress(Config->QuestProgress);
		}
	}
	InQuestLogComponent->SetCurrentActiveQuest(QuestSaveData->ActivedQuests);
	InQuestLogComponent->SetCompletedQuests(QuestSaveData->CompletedQuests);
}

void USaveLoadSubSystem::SaveQuestLog(UQuestLogComponent* InQuestLogComponent)
{
	if(!ensure(InQuestLogComponent)) return;
	if(!ensure(QuestSaveData)) return;

	QuestSaveData->ActivedQuests = InQuestLogComponent->GetCurrentActiveQuests();;
	QuestSaveData->CompletedQuests = InQuestLogComponent->GetCompletedQuests();
}

void USaveLoadSubSystem::SaveAllSaveData()
{
	SaveInventorySaveData();
	SaveLevelSaveData();
	SaveQuestSaveData();
}

void USaveLoadSubSystem::TryLoadQuestSaveData()
{
	if(UGameplayStatics::DoesSaveGameExist(QuestSaveDataSlotName,0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(QuestSaveDataSlotName,0);
		QuestSaveData = Cast<UQuestSaveData>(SaveGameObject);
		if(QuestSaveData)
		{
			Debug::Log(TEXT("QuestSaveData Load Successful"));
		}
	}
	else
	{
		Debug::Log(TEXT("QuestSaveData Load Failed"));
		USaveGame* NewSaveGameObject = UGameplayStatics::CreateSaveGameObject(UQuestSaveData::StaticClass());
		QuestSaveData = Cast<UQuestSaveData>(NewSaveGameObject);
		if(QuestSaveData)
		{
			Debug::Log(TEXT("QuestSaveData Create Slot Successful"));
		}
		else
		{
			Debug::Log(TEXT("QuestSaveData Create Slot Failed"));
		}
	}
}

void USaveLoadSubSystem::SaveQuestSaveData()
{
	if(QuestSaveData)
	{
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(QuestSaveData,
			QuestSaveDataSlotName,0);
		Debug::Log(bWasSaved ? TEXT("QuestSaveData Saved") : TEXT("QuestSaveData Not Saved"));
	}
	else
	{
		Debug::Log(TEXT("QuestSaveData is not Valid"));
	}
}

void USaveLoadSubSystem::TryLoadInventorySaveData()
{
	if(UGameplayStatics::DoesSaveGameExist(InventorySaveDataSlotName,0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(InventorySaveDataSlotName,0);
		InventorySaveData = Cast<UInventorySaveData>(SaveGameObject);
		if(InventorySaveData)
		{
			Debug::Log(TEXT("InventorySaveData Load Successful"));
		}
	}
	else
	{
		Debug::Log(TEXT("InventorySaveData Load Failed"));
		USaveGame* NewSaveGameObject = UGameplayStatics::CreateSaveGameObject(UInventorySaveData::StaticClass());
		InventorySaveData = Cast<UInventorySaveData>(NewSaveGameObject);
		if(InventorySaveData)
		{
			Debug::Log(TEXT("InventorySaveData Create Slot Successful"));
		}
		else
		{
			Debug::Log(TEXT("InventorySaveData Create Slot Failed"));
		}
	}
}

void USaveLoadSubSystem::SaveInventorySaveData()
{
	if(InventorySaveData)
	{
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(InventorySaveData,
			InventorySaveDataSlotName,0);
		Debug::Log(bWasSaved ? TEXT("InventorySaveData Saved") : TEXT("InventorySaveData Not Saved"));
	}
	else
	{
		Debug::Log(TEXT("InventorySaveData is not Valid"));
	}
}

void USaveLoadSubSystem::TryLoadLevelSaveData()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	CurrentLevelName.Append("_Data");
	Debug::Log(CurrentLevelName);

	if(UGameplayStatics::DoesSaveGameExist(CurrentLevelName,0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(CurrentLevelName,0);
		LevelSaveData = Cast<ULevelSaveData>(SaveGameObject);
		if(LevelSaveData)
		{
			Debug::Log(TEXT("LevelSaveData Load Successful"));
		}
	}
	else
	{
		Debug::Log(TEXT("InventorySaveData Load Failed"));
		USaveGame* NewSaveGameObject = UGameplayStatics::CreateSaveGameObject(ULevelSaveData::StaticClass());
		LevelSaveData = Cast<ULevelSaveData>(NewSaveGameObject);
		if(LevelSaveData)
		{
			Debug::Log(TEXT("LevelSaveData Create Slot Successful"));
		}
		else
		{
			Debug::Log(TEXT("LevelSaveData Create Slot Failed"));
		}
	}
}

void USaveLoadSubSystem::SaveLevelSaveData()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	CurrentLevelName.Append("_Data");
	Debug::Log(CurrentLevelName);

	if(LevelSaveData)
	{
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(LevelSaveData, CurrentLevelName,0);
		Debug::Log(bWasSaved ? TEXT("LevelSaveData Saved") : TEXT("LevelSaveData Not Saved"));
	}
	else
	{
		Debug::Log(TEXT("LevelSaveData is not Valid"));
	}
}

