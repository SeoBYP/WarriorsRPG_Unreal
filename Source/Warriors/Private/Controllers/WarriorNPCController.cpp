// Vince Petrelli All Rights Reserved


#include "Controllers/WarriorNPCController.h"

AWarriorNPCController::AWarriorNPCController(const FObjectInitializer& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWarriorNPCController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarriorNPCController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

