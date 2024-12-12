// Vince Petrelli All Rights Reserved


#include "Components/Quest/QuestGiverComponent.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameInstance.h"
#include "Characters/NPC/WarriorNPCCharacter.h"
#include "Components/Quest/QuestLogComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "Quest/QuestBase.h"
#include "Systems/QuestSubSystem.h"

void UQuestGiverComponent::DisplayQuestWidget_Implementation()
{
	if (QuestDataTableRowHanle.DataTable == nullptr)
	{
		Debug::Log(TEXT("NPCDataTableRowHandle's DataTable is null!"));
		return;
	}
	// 퀘스트 위젯을 화면에 표시하는 기본 로직을 여기에 구현합니다.
	// 예를 들어 로그로 출력을 해봅니다.
	UWidgetSubSystem* WidgetSubSystem = GetWorld()->GetSubsystem<UWidgetSubSystem>();
	if (WidgetSubSystem)
	{
		FQuestDataTable* QuestData = QuestDataTableRowHanle.GetRow<FQuestDataTable>(TEXT("Invalid Row Name"));
		if (!ensure(QuestData))
		{
			return;
		}
		if (UQuestGiverWidget* Widget = WidgetSubSystem->GetQuestGiverWidget())
		{
			Widget->InitializeQuestData(*QuestData, QuestDataTableRowHanle.RowName);
			if (AWarriorHeroCharacter* HeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld()))
			{
				HeroCharacter->GetHeroUIComponent()->
				               OnDisplayQuestGiverWidgetDelegate.Broadcast(*QuestData, QuestDataTableRowHanle.RowName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UQuestRewardWidget Is Null"));
		}
	}
}

void UQuestGiverComponent::DisplayQuestRewardWidget_Implementation()
{
	if (QuestDataTableRowHanle.DataTable == nullptr)
	{
		Debug::Log(TEXT("NPCDataTableRowHandle's DataTable is null!"));
		return;
	}
	// 퀘스트 위젯을 화면에 표시하는 기본 로직을 여기에 구현합니다.
	// 예를 들어 로그로 출력을 해봅니다.
	UWidgetSubSystem* WidgetSubSystem = GetWorld()->GetSubsystem<UWidgetSubSystem>();
	if (WidgetSubSystem)
	{
		FQuestDataTable* QuestData = QuestDataTableRowHanle.GetRow<FQuestDataTable>(TEXT("Invalid Row Name"));
		if (!ensure(QuestData))
		{
			return;
		}
		if (UQuestRewardWidget* Widget = WidgetSubSystem->GetQuestRewardWidget())
		{
			Widget->InitializeQuestData(*QuestData, QuestDataTableRowHanle.RowName);
			if (AWarriorHeroCharacter* HeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld()))
			{
				HeroCharacter->GetHeroUIComponent()->
				               OnDisplayQuestRewardWidgetDelegate.Broadcast(*QuestData, QuestDataTableRowHanle.RowName);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UQuestRewardWidget Is Null"));
		}
	}
}

FString UQuestGiverComponent::GetObjectiveID_Implementation()
{
	AWarriorHeroCharacter* WarriorHeroCharacter = UWarriorFunctionLibrary::GetWarriorHeroCharacter(GetWorld());
	if (!ensure(WarriorHeroCharacter))
	{
		Debug::Log(TEXT("Warrior Hero Character Is Null"));
		return TEXT("");
	}
	UQuestLogComponent* QuestLogComponent = WarriorHeroCharacter->GetQuestLogComponent();
	if (!ensure(QuestLogComponent))
	{
		Debug::Log(TEXT("Quest Log Component Is Null"));
		return TEXT("");
	}
	if (QuestDataTableRowHanle.DataTable == nullptr)
	{
		Debug::Log(TEXT("NPCDataTableRowHandle's DataTable is null!"));
		return TEXT("");
	}
// TODO : Give Quest 로직으로 수정
	bool bIsTurnedIn = false;
	bool bIsActiveQuest = QuestLogComponent->QueryActiveQuest(QuestDataTableRowHanle.RowName);
	bool bIsCompoleteQuest = QuestLogComponent->QueryCompletedQuests(QuestDataTableRowHanle.RowName, bIsTurnedIn);

	if (!bIsActiveQuest && !bIsCompoleteQuest)
	{
		if (FQuestDataTable* QuestData = QuestDataTableRowHanle.GetRow<FQuestDataTable>(TEXT("Invalid Row Name")))
		{
			if (QuestData->bAutoAccept)
			{
				QuestLogComponent->AddNewQuest(QuestDataTableRowHanle.RowName);
			}
			else
			{
				
				DisplayQuestWidget();
			}
		}
	}
	// TODO : Reward Quest 로직으로 수정
	else
	{
		if (AQuestBase* Quest = QuestLogComponent->GetQuestActor(QuestDataTableRowHanle.RowName))
		{
			if (Quest->GetIsCompleted() && !Quest->GetIsTurned())
			{
				DisplayQuestRewardWidget();
			}
		}
	}
	return ObjectiveID;
}
