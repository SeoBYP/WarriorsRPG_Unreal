// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.h"
#include "GameplayTagContainer.h"
#include "DataTables/QuestDataTable.h"
#include "HeroUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate,TSoftObjectPtr<UTexture2D>,SoftWeaponIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityIconSlotUpdatedDelegate, FGameplayTag,AbilityInputTag,TSoftObjectPtr<UMaterialInterface>,SoftAbilityIconMaterial);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FonAbilityCooldownBeginDelegate,FGameplayTag,AbilityInputTag,float, TotalCooldownTime, float, RemainingCooldownTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoneInteractedDelegate, bool, bShouldDisplayInputKey);

// Quest Delegate Start
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDisplayQuestGiverWidgetDelegate,FQuestDataTable,QuestDataTable,FName,InQuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDisplayQuestRewardWidgetDelegate,FQuestDataTable,QuestDataTable,FName,InQuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayQuestObjectiveClearNotificationDelegate,FText,InText);
// Quest Delegate End
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnAbilityIconSlotUpdatedDelegate OnAbilityIconSlotUpdated;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FonAbilityCooldownBeginDelegate OnAbilityCooldownBegin;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnStoneInteractedDelegate OnStoneInteracted;

	// Quest Delegate Start
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnDisplayQuestGiverWidgetDelegate OnDisplayQuestGiverWidgetDelegate;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnDisplayQuestRewardWidgetDelegate OnDisplayQuestRewardWidgetDelegate;

	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnDisplayQuestObjectiveClearNotificationDelegate OnDisplayQuestObjectiveClearNotificationDelegate;
	// Quest Delegate End
};
