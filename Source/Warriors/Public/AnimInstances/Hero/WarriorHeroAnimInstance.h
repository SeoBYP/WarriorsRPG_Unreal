﻿// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIORS_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="AnimData|Refrence")
	AWarriorHeroCharacter* OwningHeroCharacter;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AnimData|LocomotionData")
	bool bShouldEnterRelaxState;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.0f;

	float IdleElapsedTime;
};
