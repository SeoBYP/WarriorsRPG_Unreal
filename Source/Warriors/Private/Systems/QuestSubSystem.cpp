// Vince Petrelli All Rights Reserved


#include "Systems/QuestSubSystem.h"

void UQuestSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	LoadQuestDataTable();
}

void UQuestSubSystem::Deinitialize()
{
	Super::Deinitialize();
}

void UQuestSubSystem::LoadQuestDataTable()
{
	QuestDataTable = Cast<UDataTable>(
		StaticLoadObject(UDataTable::StaticClass(),nullptr,
			TEXT("/Script/Engine.DataTable'/Game/DataTables/Quest/DT_QuestDataTable.DT_QuestDataTable'")));
	if (QuestDataTable)
	{
		UE_LOG(LogTemp, Log, TEXT("QuestDataTable loaded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("QuestDataTable could not be loaded."));
	}
}
