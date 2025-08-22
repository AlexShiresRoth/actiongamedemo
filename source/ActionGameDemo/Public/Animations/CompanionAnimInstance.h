// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CompanionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UCompanionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSpeed{0.0f};

	UFUNCTION(BlueprintCallable, Category= Animation)
	void UpdateSpeed();
};
