// Vince Petrelli All Rights Reserved


#include "WarriorHeroWeapon.h"


// Sets default values
AWarriorHeroWeapon::AWarriorHeroWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWarriorHeroWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarriorHeroWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

