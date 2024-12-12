// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "QuestSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API UQuestSubSystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;  // 필요한 경우 레벨 전환 시 수행할 작업을 추가

private:
	UFUNCTION()
	void LoadQuestDataTable();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Data | Quest",meta=(AllowPrivateAccess))
	UDataTable* QuestDataTable;

public:
	FORCEINLINE UDataTable* GetQuestDataTable() const { return QuestDataTable; }
};
