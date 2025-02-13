// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/BossAnimInstance.h"

void UBossAnimInstance::UpdateSpeed()
{
    APawn *PawnRef{TryGetPawnOwner()};

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
