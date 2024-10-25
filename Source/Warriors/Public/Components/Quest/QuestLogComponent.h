// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "QuestLogComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted,AQuestBase*,QuestActor);

class AQuestBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),BlueprintType,Blueprintable)
class WARRIORS_API UQuestLogComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	TArray<FName> CurrentActiveQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	TArray<FName> CompletedQuests;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	FName CurrentTrackedQuest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Quest", meta=(AllowPrivateAccess=true))
	TArray<AQuestBase*> CurrentQuests;

public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable,Category="Quest|Action")
	FOnQuestCompleted OnQuestCompleted;
};
