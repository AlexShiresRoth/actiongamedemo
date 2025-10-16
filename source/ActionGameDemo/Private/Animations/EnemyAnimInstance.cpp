// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/EnemyAnimInstance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Regular_Enemy.h"
#include "Interfaces/Enemy.h"

void UEnemyAnimInstance::UpdateSpeed()
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
