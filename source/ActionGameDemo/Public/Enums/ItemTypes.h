// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum EItemTypes
{
	Healing UMETA(DisplayName = "Healing"),
	StaminaBoost UMETA(DisplayName = "Stamina"),
	Ability UMETA(DisplayName = "Ability"),
	WeaponType UMETA(DisplayName = "Weapon"),
	ArmorType UMETA(DisplayName = "Armor"),
	ShieldType UMETA(DisplayName = "Shield"),
	SpecialType UMETA(DisplayName = "Special"),
};
