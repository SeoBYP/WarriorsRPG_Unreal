// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "SaveGame/InventorySaveData.h"
#include "SaveGame/LevelSaveData.h"
#include "SaveGame/QuestSaveData.h"
#include "Subsystems/Subsystem.h"
#include "SaveLoadSubSystem.generated.h"

/**
 * 
 */

UCLASS()
class WARRIORS_API USaveLoadSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	UInventorySaveData* InventorySaveData;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	UQuestSaveData* QuestSaveData;
	
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	ULevelSaveData* LevelSaveData;
	
private:
	FString InventorySaveDataSlotName = "InventorySaveData";
	FString QuestSaveDataSlotName = "QuestSaveData";
	void TryLoadAllSaveData();

public:
	UFUNCTION(BlueprintCallable)
	void SaveQuestDetails(AQuestBase* Quest);

	UFUNCTION(BlueprintCallable)
	void LoadQuests(UQuestLogComponent* InQuestLogComponent);

	UFUNCTION(BlueprintCallable)
	void SaveQuestLog(UQuestLogComponent* InQuestLogComponent);
	
public:
	UFUNCTION(BlueprintCallable)
	void SaveAllSaveData();

	UFUNCTION(BlueprintCallable)
	void TryLoadQuestSaveData();

	UFUNCTION(BlueprintCallable)
	void SaveQuestSaveData();
	
	UFUNCTION(BlueprintCallable)
	void TryLoadInventorySaveData();

	UFUNCTION(BlueprintCallable)
	void SaveInventorySaveData();
	
	UFUNCTION(BlueprintCallable)
	void TryLoadLevelSaveData();

	UFUNCTION(BlueprintCallable)
	void SaveLevelSaveData();
	
	FORCEINLINE UInventorySaveData* GetInventorySaveData() const { return InventorySaveData; }
	FORCEINLINE ULevelSaveData* GetLevelSaveData() const { return LevelSaveData; }
	FORCEINLINE UQuestSaveData* GetQuestSaveData() const { return QuestSaveData; }
};
