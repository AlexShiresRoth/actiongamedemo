// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/BlockAbility.h"
#include "Interfaces/IChargeAttack.h"
#include "Interfaces/UltimateAttack.h"
#include "BossAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UBossAnimInstance : public UAnimInstance, public IIChargeAttack, public IBlockAbility,
                                             public IUltimateAttack
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Boss Anim Instance")
	float CurrentSpeed{0.0f};

	UFUNCTION(BlueprintCallable, Category = "Boss Anim Instance")
	void UpdateSpeed();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Anim Instance")
	bool bIsCharging{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Anim Instance")
	bool bIsDead{false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsInUltimateState{false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsBlocking{false};

	UPROPERTY(BlueprintReadWrite, Category=Ultimate)
	bool bIsUltimateFinished{false};

	virtual bool GetIsUltimateFinished_Implementation() override
	{
		return bIsUltimateFinished;
	}

	virtual void SetIsUltimateFinished_Implementation(bool val) override
	{
		bIsUltimateFinished = val;
	}

	virtual void SetIsCharging_Implementation(bool bCharging) override
	{
		bIsCharging = bCharging;
	}

	virtual void SetIsBlocking_Implementation(const bool bIsBlockingState) override
	{
		bIsBlocking = bIsBlockingState;
	}

	bool GetIsBlocking() const
	{
		return bIsBlocking;
	}

	virtual void SetIsUltimateState_Implementation(const bool bIsUltimate) override
	{
		bIsInUltimateState = bIsUltimate;
	}
};
