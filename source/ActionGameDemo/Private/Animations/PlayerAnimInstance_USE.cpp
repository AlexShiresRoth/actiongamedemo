// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Animations/PlayerAnimInstance_USE.h"

void UPlayerAnimInstance_USE::UpdateSpeed()
{
	APawn* PawnRef{TryGetPawnOwner()};

	if (!IsValid(PawnRef))
	{
		return;
	}
	// curly braces only work with newly declared variables
	FVector Velocity{PawnRef->GetVelocity()};
	// explicit casting is not required but is good practice
	float VectorLength{static_cast<float>(Velocity.Length())};

	CurrentSpeed = VectorLength;
}

void UPlayerAnimInstance_USE::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance_USE::UpdateDirection()
{
	APawn* PawnRef{TryGetPawnOwner()};

	if (!IsValid(PawnRef))
	{
		return;
	}

	if (!bIsInCombat)
	{
		return;
	}

	// this produces a result between -180 and 180
	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation());
}
