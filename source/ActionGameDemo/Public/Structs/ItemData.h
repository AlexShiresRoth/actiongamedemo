// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Enums/EItemTypeMacro.h"
#include "Enums/ItemTypes.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemTypeKVPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemTypes> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TypeValue;
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemTypeMacro> ItemTypeMacro;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemTypeKVPair TypePair;
};
