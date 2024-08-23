// Vince Petrelli All Rights Reserved


#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "Characters/WarriorsBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarriorsBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		 OwningMovementComponent = OwningCharacter->GetCharacterMovement();

	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
