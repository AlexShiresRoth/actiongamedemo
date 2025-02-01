// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UPlayerAnimInstance : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Player Anim Instance")
	float CurrentVelocity{0.0f};
};
