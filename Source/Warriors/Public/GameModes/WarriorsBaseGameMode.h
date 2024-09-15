// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WarriorTypes/WarriorEnumTypes.h"
#include "WarriorsBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API AWarriorsBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWarriorsBaseGameMode();

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Game Settings")
	EWarriorGameDifficulty CurrentGameDefficulty;

public:
	FORCEINLINE EWarriorGameDifficulty GetWarriorGameDifficulty() const { return CurrentGameDefficulty; }
};
