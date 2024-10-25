// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WarriorAIController.h"
#include "WarriorNPCController.generated.h"

UCLASS()
class WARRIORS_API AWarriorNPCController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWarriorNPCController(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="NPC | Dialogue")
	UBehaviorTree* DialogueTree;

public:
	FORCEINLINE UBehaviorTree* GetDiagloueTree() const { return DialogueTree; }
};
