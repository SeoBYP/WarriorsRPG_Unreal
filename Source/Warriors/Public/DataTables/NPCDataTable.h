// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NPCDataTable.generated.h"

UENUM(BlueprintType, meta = (ScriptName="NPCType"))
enum class ENPCType: uint8
{
	ENT_Humanoid UMETA(DisplayName = "Humanoid"),
	ENT_Animal UMETA(DisplayName = "Animal"),
};

UENUM(BlueprintType, meta = (ScriptName="NPCSubType"))
enum class ENPCSubType : uint8
{
	ENS_Trader UMETA(DisplayName = "Trader"),
	ENS_QuestGiver UMETA(DisplayName = "Quest Giver"),
	ENS_Enemy UMETA(DisplayName = "Enemy"),
	ENS_Uninteractable UMETA(DisplayName = "Uninteractable"),
	ENS_QuestSubject UMETA(DisplayName = "Quest Subject"),
	ENS_Talker UMETA(DisplayName = "Talker"),
};

USTRUCT(BlueprintType)
struct FNPCDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="NPC Properties")
	FString ID;
	
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="NPC Properties")
	FText Name = FText::FromString("WorldNPC");

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="NPC Properties")
	ENPCType NPCType;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly,Category="NPC Properties")
	ENPCSubType NPCSubType;
};
