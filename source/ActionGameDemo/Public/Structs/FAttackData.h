// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FAttackData.generated.h"

USTRUCT(BlueprintType)
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Attacker;
	UPROPERTY()
	FVector LaunchVelocity;
};
