// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WarriorsHeroController.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORS_API AWarriorsHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AWarriorsHeroController();
	
	//~ Begin IGenericTeamAgentInterface Interface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface
private:
	FGenericTeamId HeroTeamId;

};
