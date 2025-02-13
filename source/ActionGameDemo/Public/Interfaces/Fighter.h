// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Fighter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFighter : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ACTIONGAMEDEMO_API IFighter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// virtual tells c++ this function can be overridden
	virtual float GetDamage() { return 0.0f; };

	virtual void Attack() {}

	virtual float GetAnimDuration() { return 0.0f; };

	virtual float GetMeleeRange() { return 0.0f; };
};
