// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Enums/ItemContext.h"
#include "Structs/ItemData.h"
#include "ItemWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAddItemToInventorySignature, UItemWidget,
	OnAddItemToInventoryDelegate, FString, ItemID
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnItemActionsMenuTriggerSignature, UItemWidget,
                                                   OnItemActionsMenuDelegate, FItemData, Item);

UCLASS(BlueprintType, Blueprintable)
class ACTIONGAMEDEMO_API UItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData ItemData;

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemContextType> ItemLocation;

	UPROPERTY(BlueprintAssignable)
	FOnAddItemToInventorySignature OnAddItemToInventoryDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnItemActionsMenuTriggerSignature OnItemActionsMenuDelegate;
};
