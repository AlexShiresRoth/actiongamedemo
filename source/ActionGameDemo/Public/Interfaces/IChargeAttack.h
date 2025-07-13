// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IChargeAttack.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIChargeAttack : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONGAMEDEMO_API IIChargeAttack
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetIsCharging(bool bCharging);
};
