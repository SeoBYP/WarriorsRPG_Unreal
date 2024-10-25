// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "SaveGame/InventorySaveData.h"
#include "WarriorGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FWarriorGameLevelSet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, meta=(Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};

/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

protected:
	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWarriorGameLevelSet> GameLevelSets;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UUserWidget* HeroHUD;
	
public:
	UFUNCTION(BlueprintCallable, meta=(GameplayTagFileter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;

	UFUNCTION(BlueprintCallable, Category="HUD")
	void SetHeroHUD(UUserWidget* InHeroHUD) { HeroHUD = InHeroHUD; }

	UFUNCTION(BlueprintCallable, Category="HUD")
	UUserWidget* GetHeroHUD() const { return HeroHUD; }
};
