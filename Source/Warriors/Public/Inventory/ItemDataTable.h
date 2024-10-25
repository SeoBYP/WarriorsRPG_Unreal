// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EItemType.h"
#include "ItemDataTable.generated.h"
/**
 * 
 */
// 추루 Warrior Stone과 통합해서 관리할 예정입니다.
USTRUCT(Blueprintable,BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName Description;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 StackSize;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AActor> ItemEffect;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	EItemType Category;
};
