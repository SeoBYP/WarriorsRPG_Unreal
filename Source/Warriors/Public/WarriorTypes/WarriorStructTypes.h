// Vince Petrelli All Rights Reserved

#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "WarriorEnumTypes.h"
#include "WarriorStructTypes.generated.h"

class UWarriorHeroGameplayAbility;
class UInputMappingContext;
class UWarriorHeroLinkedAnimLayer;
class UWarriorGameplayAbility;

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UWarriorHeroGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};


USTRUCT(BlueprintType)
struct FWarriorHeroSpecialAbilitySet : public FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(Categories="Player.Cooldown"))
	TSoftObjectPtr<UMaterialInterface> SoftAbilityIconMaterial;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AbilityCooldownTag;
	
};

USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UWarriorHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(TitleProperty = "InputTag"))
	TArray<FWarriorHeroSpecialAbilitySet> SpecialWeaponAbilities;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;
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

USTRUCT(BlueprintType,Blueprintable)
struct FStageDetails
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText StageName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FObjectiveDetails> Objectives;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 XPReward;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TMap<FName,int32> ItemRewards;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 CurrencyRewards;
};
