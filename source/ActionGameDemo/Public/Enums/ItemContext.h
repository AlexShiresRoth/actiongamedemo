// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EItemContextType
{
	ItemContainer UMETA(DisplayName = "Items Container"),
	Inventory UMETA(DisplayName = "Inventory"),
};
