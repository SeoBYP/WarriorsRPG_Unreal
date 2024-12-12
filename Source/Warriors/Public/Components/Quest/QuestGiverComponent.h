// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "DataTables/QuestDataTable.h"
#include "Interfaces/QuestInterafece.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "QuestGiverComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),BlueprintType,Blueprintable)
class WARRIORS_API UQuestGiverComponent : public UPawnExtensionComponentBase,
public IQuestInterafece
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Quest|Data",meta=(AllowPrivateAccess="true"))
	FString ObjectiveID;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Quest|Data",meta=(AllowPrivateAccess="true"))
	FDataTableRowHandle QuestDataTableRowHanle;

public:
	virtual FString GetObjectiveID_Implementation() override;
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Quest|Display",meta=(AllowPrivateAccess="true"))
	void DisplayQuestWidget();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Quest|Display",meta=(AllowPrivateAccess="true"))
	void DisplayQuestRewardWidget();

	FORCEINLINE bool HasQuest() const{return QuestDataTableRowHanle.DataTable != nullptr;}
	FORCEINLINE FName GetQuestDataTableRowName() const{return QuestDataTableRowHanle.RowName;}
};
