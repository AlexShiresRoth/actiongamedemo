// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/IChargeAttack.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UEnemyAnimInstance : public UAnimInstance, public IIChargeAttack
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{0.0f};

	UFUNCTION(BlueprintCallable, Category= Animation)
	void UpdateSpeed();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsCharging{false};

	virtual void SetIsCharging_Implementation(bool bCharging) override
	{
		bIsCharging = bCharging;
	}
};
