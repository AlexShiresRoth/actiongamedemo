// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum EEQuipmentSlot
{
	Armor UMETA(DisplayName = "Armor"),
	Sword UMETA(DisplayName = "Sword"),
	Shield UMETA(DisplayName = "Shield"),
	Special UMETA(DisplayName = "Special"),
};
