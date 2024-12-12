// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WarriorWidgetBase.h"
#include "QuestTrackerWidget.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UQuestTrackerWidget : public UWarriorWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Quest Data", meta=(AllowPrivateAccess="true"))
	AQuestBase* CurrentQuestActor;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentQuestActor(AQuestBase* InCurrentQuestActor) {CurrentQuestActor = InCurrentQuestActor;}

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Quest Data")
	void OnUpdateQuestTrackerWidget(AQuestBase* InQuestBase);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Quest Data")
	void OnObjectiveUpdated();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Quest Data")
	void OnObjectiveCompleted(AQuestBase* InQuestBase);
};
