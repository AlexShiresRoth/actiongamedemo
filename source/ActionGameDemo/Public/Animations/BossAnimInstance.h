// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/IChargeAttack.h"
#include "BossAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UBossAnimInstance : public UAnimInstance, public IIChargeAttack
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

	virtual void SetIsCharging_Implementation(bool bCharging) override
	{
		bIsCharging = bCharging;
	}
};
