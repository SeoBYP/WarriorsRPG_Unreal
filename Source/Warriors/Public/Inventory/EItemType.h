// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"

// ReSharper disable once UnrealHeaderToolWarning
UENUM(BlueprintType,meta=(Bitflags,UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EItemType : uint8
{
	None        = 0,        // 0: 기본값으로 사용할 None 추가
	Food		= 1 << 0, // 1
	Materials	= 1 << 1, // 2
	Equipment	= 1 << 2, // 4
	Potions		= 1 << 3, // 8
	Junk		= 1 << 4, // 16
};
