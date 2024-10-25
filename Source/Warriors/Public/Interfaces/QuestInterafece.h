// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestInterafece.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UQuestInterafece : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WARRIORS_API IQuestInterafece
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Quest")
	FString GetObjectiveID();
	
};
