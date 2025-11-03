// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum FBossState
{
	BossState_None UMETA(DisplayName = "None"),
	BossState_Invulnerable UMETA(DisplayName = "Invulnerable"),
};
