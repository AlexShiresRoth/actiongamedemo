// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Enums/ItemContext.h"
#include "ItemWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAddItemToInventorySignature, UItemWidget,
	OnAddItemToInventoryDelegate, FText, ItemID
);

UCLASS(BlueprintType, Blueprintable)
class ACTIONGAMEDEMO_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemContextType> ItemLocation;

	UPROPERTY(BlueprintAssignable)
	FOnAddItemToInventorySignature OnAddItemToInventoryDelegate;
};
