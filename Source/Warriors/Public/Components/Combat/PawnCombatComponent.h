// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"


class AWarriorWeaponBase;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquipeedWeapon,
	LeftHand,
	RightHand,
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORS_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UPROPERTY(BlueprintReadWrite,Category="Warriors|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable,Category="Warriors|Combat")
	void ToggleWeaponCollision(bool bShouldEnable,EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquipeedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	TArray<AActor*> OverllapedActors;
	
private:
	TMap<FGameplayTag,AWarriorWeaponBase*> CharacterCarriedWeaponMap;

	
};
