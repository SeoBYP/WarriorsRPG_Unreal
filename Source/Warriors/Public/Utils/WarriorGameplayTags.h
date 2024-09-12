﻿// Vince Petrelli All Rights Reserved

#pragma once
#include "NativeGameplayTags.h"

/** 사용자 입력에 대한 커스텀 GamePlayTags 입니다.*/
namespace WarriorsGameplayTags
{
	/** Input Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnEquipAxe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Light)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Heavy)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PickUp_Stones)
	
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Rage)

	/** Player Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UnEquip_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPuase)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Rage)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Light)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Heavy)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_PickUp_Stones)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Light)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Heavy)
	
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

	/** Player Event Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPuase)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActivateRage)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_AOE)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ComsumeStones)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Activating)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Active)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Full)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_None)
	
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy)

	/** Enemy Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnStone)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Unblockable)

	/** Shared Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead)

	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Invincible)
}
