// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance_USE.generated.h"

/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UPlayerAnimInstance_USE : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Player Anim Instance")
	float CurrentVelocity{0.0f};

	UFUNCTION(BlueprintCallable, Category = "Player Anim Instance")
	void UpdateVelocity();
};
