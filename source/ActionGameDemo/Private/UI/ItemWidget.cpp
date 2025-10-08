// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

void UItemWidget::AddItemToInventory()
{
	if (ItemData.ID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Item data not provided"));
		return;
	}
	switch (ItemLocation)
	{
	case Inventory:
		UE_LOG(LogTemp, Warning, TEXT("Item data provided %s"), *ItemData.ID);
		OnItemActionsMenuDelegate.Broadcast(ItemData);
		break;
	case ItemContainer:
		OnAddItemToInventoryDelegate.Broadcast(ItemData.ID);
		this->RemoveFromParent();
		break;
	default:
		return;
	}
}
