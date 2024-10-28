// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chest.generated.h"

class UInventoryComponent;
class UInteractableComponent;

UCLASS()
class WARRIORS_API AChest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// Components
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="StaticMesh",meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components|Interactable",meta=(allowPrivateAccess="true"))
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components|Inventory",meta=(allowPrivateAccess="true"))
	UInventoryComponent* InventoryComponent;
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components|Interactable")
	TWeakObjectPtr<UDataTable> InteractableDataTable;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Components|Interactable")
	FName InteractableName;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
