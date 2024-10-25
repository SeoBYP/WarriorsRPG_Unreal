// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "InteractableDataTable.generated.h"

UENUM(BlueprintType, meta = (ScriptName="Damage_Type"))
enum class EInteractionType : uint8
{
	EIT_Press UMETA(DisplayName="Press"),
	EIT_Hold UMETA(DisplayName="Hold")
};

USTRUCT(BlueprintType)
struct FInteractableDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Widget")
	FText DisplayText = FText::FromString("Placeholder Text");

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Widget")
	FText TooltipText = FText::FromString("Placeholder Text");

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Detection")
	float MaxHoverDistanceFromCharacter = 350.f;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Detection")
	float MaxHoverDistanceFromScreenCenter = 50.f;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Detection")
	float MaxOverlapDistance = 700.0f;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Detection")
	bool bDetectWhenObstructed = false;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Detection")
	bool bAllowInteractionWhenObstructed = false;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Detection")
	TEnumAsByte<ECollisionChannel> ObstructionTraceChannel = ECC_Camera;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Interaction")
	TArray<FString> Keys = {"DefaultKey"};
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Interaction")
	EInteractionType InteractionType = EInteractionType::EIT_Press;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Interaction")
	float InteractionDuration = 1.0f;
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="Interaction")
	float DelayBetweenInteraction = 0.5f;
};
