// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum ECompanionState
{
	Companion_Idle UMETA(DisplayName = "Idle"),
	Companion_Following UMETA(DisplayName = "Following"),
	Companion_Range UMETA(DisplayName = "Range"),
	Companion_Charge UMETA(DisplayName = "Charge"),
	Companion_Melee UMETA(DisplayName = "Melee"),
	Companion_Downed UMETA(DisplayName = "Downed"),
	Companion_GameOver UMETA(DisplayName = "Game Over"),
};
