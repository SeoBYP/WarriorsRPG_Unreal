﻿// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class WARRIORS_API AWarriorPickUpBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWarriorPickUpBase();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pick UP Interaction")
	USphereComponent* PickUpCollisionSphere;

	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
