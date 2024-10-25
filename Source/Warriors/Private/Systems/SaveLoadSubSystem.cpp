// Vince Petrelli All Rights Reserved


#include "Systems/SaveLoadSubSystem.h"

#include "WarriorDebugHelper.h"
#include "Kismet/GameplayStatics.h"

void USaveLoadSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TryLoadAllSaveData();
	Debug::DebugLog(TEXT("SaveLoadSubSystem Initialized"));
}

void USaveLoadSubSystem::Deinitialize()
{
	Super::Deinitialize();
	SaveAllSaveData();
	Debug::DebugLog(TEXT("SaveLoadSubSystem Reinitialized"));
}

void USaveLoadSubSystem::TryLoadAllSaveData()
{
	TryLoadInventorySaveData();
	TryLoadLevelSaveData();
}

void USaveLoadSubSystem::SaveAllSaveData()
{
	SaveInventorySaveData();
	SaveLevelSaveData();
}

void USaveLoadSubSystem::TryLoadInventorySaveData()
{
	if(UGameplayStatics::DoesSaveGameExist(InventorySaveDataSlotName,0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(InventorySaveDataSlotName,0);
		InventorySaveData = Cast<UInventorySaveData>(SaveGameObject);
		if(InventorySaveData)
		{
			Debug::DebugLog(TEXT("InventorySaveData Load Successful"));
		}
	}
	else
	{
		Debug::DebugLog(TEXT("InventorySaveData Load Failed"));
		USaveGame* NewSaveGameObject = UGameplayStatics::CreateSaveGameObject(UInventorySaveData::StaticClass());
		InventorySaveData = Cast<UInventorySaveData>(NewSaveGameObject);
		if(InventorySaveData)
		{
			Debug::DebugLog(TEXT("InventorySaveData Create Slot Successful"));
		}
		else
		{
			Debug::DebugLog(TEXT("InventorySaveData Create Slot Failed"));
		}
	}
}

void USaveLoadSubSystem::SaveInventorySaveData()
{
	if(InventorySaveData)
	{
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(InventorySaveData,
			InventorySaveDataSlotName,0);
		Debug::DebugLog(bWasSaved ? TEXT("InventorySaveData Saved") : TEXT("InventorySaveData Not Saved"));
	}
	else
	{
		Debug::DebugLog(TEXT("InventorySaveData is not Valid"));
	}
}

void USaveLoadSubSystem::TryLoadLevelSaveData()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	CurrentLevelName.Append("_Data");
	Debug::DebugLog(CurrentLevelName);

	if(UGameplayStatics::DoesSaveGameExist(CurrentLevelName,0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(CurrentLevelName,0);
		LevelSaveData = Cast<ULevelSaveData>(SaveGameObject);
		if(LevelSaveData)
		{
			Debug::DebugLog(TEXT("LevelSaveData Load Successful"));
		}
	}
	else
	{
		Debug::DebugLog(TEXT("InventorySaveData Load Failed"));
		USaveGame* NewSaveGameObject = UGameplayStatics::CreateSaveGameObject(ULevelSaveData::StaticClass());
		LevelSaveData = Cast<ULevelSaveData>(NewSaveGameObject);
		if(LevelSaveData)
		{
			Debug::DebugLog(TEXT("LevelSaveData Create Slot Successful"));
		}
		else
		{
			Debug::DebugLog(TEXT("LevelSaveData Create Slot Failed"));
		}
	}
}

void USaveLoadSubSystem::SaveLevelSaveData()
{
	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	CurrentLevelName.Append("_Data");
	Debug::DebugLog(CurrentLevelName);

	if(LevelSaveData)
	{
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(LevelSaveData, CurrentLevelName,0);
		Debug::DebugLog(bWasSaved ? TEXT("LevelSaveData Saved") : TEXT("LevelSaveData Not Saved"));
	}
	else
	{
		Debug::DebugLog(TEXT("LevelSaveData is not Valid"));
	}
}

