// Vince Petrelli All Rights Reserved

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

	/** Player Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

	/** Player Event Tags*/
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
	WARRIORS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Axe)
}
