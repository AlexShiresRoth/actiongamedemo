// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.generated.h"

USTRUCT(BlueprintType)
struct ACTIONGAMEDEMO_API FTraceSockets
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, Category = "Trace")
	FName Start;

	UPROPERTY(EditAnywhere, Category = "Trace")
	FName End;

	UPROPERTY(EditAnywhere, Category = "Trace")
	FName Rotation;
};
