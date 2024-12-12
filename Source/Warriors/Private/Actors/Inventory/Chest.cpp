// Vince Petrelli All Rights Reserved


#include "Actors/Inventory/Chest.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "Components/Interaction/InteractableComponent.h"
#include "Components/Inventory/InventoryComponent.h"
#include "Runtime/Core/Tests/Containers/TestUtils.h"


// Sets default values
AChest::AChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(Mesh);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	if (InteractableDataTable.IsValid())
	{
		InteractableComponent->SetInteractableDataBasedOnDataTable(InteractableDataTable.Get(), InteractableName);
	}
	
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
