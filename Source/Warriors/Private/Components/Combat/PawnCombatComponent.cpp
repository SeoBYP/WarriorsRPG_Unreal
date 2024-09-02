// Vince Petrelli All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"
#include "Warriors/Public/WarriorDebugHelper.h"
#include "Warriors/Public/Items/Weapons/WarriorWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
	AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),TEXT("A named named %s has already been added as carried weapon"),*InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister,InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this,&ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this,&ThisClass::OnWeaponPulledFromTargetActor);
	
	if(bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
	const FString WeaponString = FString::Printf( TEXT("A Weapon named : %s has been registered using the tag %s"),*InWeaponToRegister->GetName(),*InWeaponTagToRegister.ToString());
	Debug::DebugLog(WeaponString);
}

// 캐릭터가 소지한 특정 태그의 무기를 반환하는 함수
// InWeaponTagToGet: 조회할 무기의 태그
// 반환값: 찾은 무기 객체 또는 null
AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	// 해당 태그의 무기가 맵에 존재하는지 확인
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		// 무기를 찾아서 반환
		//AWarriorWeaponBase* const* FoundWeapon로 받는 이유는 Find 함수가 AWarriorWeaponBase* 타입의 포인터에 대한 포인터를 반환하기 때문입니다.
		//이 포인터는 맵에서 검색된 무기를 가리키며, 이를 통해 실제 무기 객체에 접근할 수 있습니다.
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon; // 포인터를 반환
		}
	}
	return nullptr; // 태그에 해당하는 무기가 없으면 null 반환
}


AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if(ToggleDamageType == EToggleDamageType::CurrentEquipeedWeapon)
	{
		AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

		check(WeaponToToggle);

		if(bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

			OverllapedActors.Empty();
		}
	}

	
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
