// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WarriorWidgetBase.h"
#include "QuestClearNotifyWidget.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UQuestClearNotifyWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Quest Data", meta=(AllowPrivateAccess="true",ExposeOnSpawn= "true"))
	FText InText;
};
