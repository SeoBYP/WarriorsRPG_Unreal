// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WarriorWidgetBase.h"
#include "QuestLogWidget.generated.h"

class AQuestBase;
/**
 * 
 */
UCLASS()
class WARRIORS_API UQuestLogWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Quest Data", meta=(AllowPrivateAccess="true"))
	AQuestBase* CurrentQuestActor;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentQuestActor(AQuestBase* InCurrentQuestActor){CurrentQuestActor = InCurrentQuestActor;}
};
