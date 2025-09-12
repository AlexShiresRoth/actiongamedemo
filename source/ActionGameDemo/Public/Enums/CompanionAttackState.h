// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ECompanionAttackState
{
	Attack_Idle UMETA(DisplayName = "Idle"),
	Attack_Aiming UMETA(DisplayName = "Aiming"),
	Attack_Firing UMETA(DisplayName = "Firing"),
	Attack_Recovering UMETA(DisplayName = "Recovering"),
};
