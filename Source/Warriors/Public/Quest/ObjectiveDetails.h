// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ObjectiveDetails.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	Location,
	Kill,
	Interact,
	Collect,
};

USTRUCT(BlueprintType,Blueprintable)
struct FObjectiveDetails
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText ObjectiveName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	EObjectiveType Type;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FString ObjectiveID;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	bool IsOptional;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 BonusXP;
};