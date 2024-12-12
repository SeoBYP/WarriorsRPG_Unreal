// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataTables/QuestDataTable.h"
#include "Widgets/WarriorWidgetBase.h"
#include "QuestRewardWidget.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UQuestRewardWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Quest Data", meta=(AllowPrivateAccess="true",ExposeOnSpawn= "true"))
	FQuestDataTable QuestDataTable;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Quest Data", meta=(AllowPrivateAccess="true",ExposeOnSpawn= "true"))
	FName QuestID;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeQuestData(FQuestDataTable InQuestDataTable, FName InQuestID);

	UFUNCTION()
	FORCEINLINE FQuestDataTable GetQuestDataTable() const {return QuestDataTable;}
};
