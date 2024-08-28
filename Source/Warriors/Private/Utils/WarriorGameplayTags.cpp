// Vince Petrelli All Rights Reserved


#include "Utils/WarriorGameplayTags.h"

/** 사용자 입력에 대한 커스텀 GamePlayTags 입니다.*/
namespace WarriorsGameplayTags
{
	/** Input Tags*/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe,"InputTag.EquipAxe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipAxe,"InputTag.UnEquipAxe")
	
	/** Player Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe,"Player.Weapon.Axe")

	/** Player Event Tags*/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe,"Player.Event.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Axe,"Player.Event.UnEquip.Axe")
}
