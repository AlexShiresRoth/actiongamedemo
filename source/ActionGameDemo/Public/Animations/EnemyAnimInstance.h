// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/BlockAbility.h"
#include "Interfaces/IChargeAttack.h"
#include "Interfaces/UltimateAttack.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UEnemyAnimInstance : public UAnimInstance, public IIChargeAttack, public IBlockAbility,
                                              public IUltimateAttack
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

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead{false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsInUltimateState{false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsBlocking{false};

	virtual void SetIsBlocking_Implementation(const bool bIsBlockingState) override
	{
		bIsBlocking = bIsBlockingState;
	}

	UFUNCTION()
	bool GetIsBlocking() const
	{
		return bIsBlocking;
	}

	UFUNCTION()
	virtual void SetIsUltimateState_Implementation(const bool bIsUltimate) override
	{
		bIsInUltimateState = bIsUltimate;
	}

	virtual void SetIsCharging_Implementation(const bool bCharging) override
	{
		bIsCharging = bCharging;
	}
};
