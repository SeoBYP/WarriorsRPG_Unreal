// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PawnExtensionComponentBase.h"
#include "ItemDataComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent),Blueprintable,BlueprintType)
class WARRIORS_API UItemDataComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UItemDataComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	FDataTableRowHandle ItemID;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Item", meta=(AllowPrivateAccess="true"))
	int32 Quantity = 1;
};
