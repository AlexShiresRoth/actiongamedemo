// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

void UItemWidget::AddItemToInventory()
{
	if (!ItemName.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("ITEMWIDGET::Adding %s to inventory"), *ItemName.ToString());
	}

	OnAddItemToInventoryDelegate.Broadcast(ItemID);
}
