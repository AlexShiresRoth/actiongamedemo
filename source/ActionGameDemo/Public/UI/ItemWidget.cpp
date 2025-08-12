// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

// TODO i added item context location, we need to dynamically use this to tell it to be in the inventory component
void UItemWidget::AddItemToInventory()
{
	if (ItemName.IsEmpty() || ItemLocation == Inventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("ITEMWIDGET::Adding %s to inventory"), *ItemName.ToString());
		return;
	}
	OnAddItemToInventoryDelegate.Broadcast(ItemID);
	this->RemoveFromParent();
}
