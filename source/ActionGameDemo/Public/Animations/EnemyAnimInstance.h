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

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead{false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsInUltimateState{false};

	UPROPERTY(BlueprintReadOnly)
	bool bIsBlocking{false};

	UFUNCTION()
	void SetIsBlocking(const bool bIsBlockingState)
	{
		UE_LOG(LogTemp, Error, TEXT("SetIsBlocking"));
		bIsBlocking = bIsBlockingState;
	}

	UFUNCTION()
	bool GetIsBlocking() const
	{
		return bIsBlocking;
	}

	UFUNCTION()
	void SetIsUltimateState(const bool bIsUltimate)
	{
		bIsInUltimateState = bIsUltimate;
	}

	virtual void SetIsCharging_Implementation(const bool bCharging) override
	{
		bIsCharging = bCharging;
	}
};
