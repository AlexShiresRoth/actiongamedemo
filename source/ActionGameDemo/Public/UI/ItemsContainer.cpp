// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemsContainer.h"
#include "ItemWidget.h"
#include "Interactable/Item.h"


void UItemsContainer::SetItems(TArray<class AItem*> Items)
{
	if (!ScrollContainer || !IsValid(ItemWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("UITEMSCONTAINER::Scrollcontainer or ItemWidgetClass is null"));
		return;
	}

	if (Items.Num() > 0)
	{
		for (AItem* Item : Items)
		{
			if (Item)
			{
				if (UItemWidget* ItemWidget = CreateWidget<UItemWidget>(this, ItemWidgetClass))
				{
					ItemWidget->ItemName = FText::FromName(Item->ItemData.Name);
					ItemWidget->ItemID = FText::FromName(Item->ItemData.ID);
					ItemWidget->ItemIcon = Item->ItemData.ItemIcon;
					ItemWidget->Description = Item->ItemData.Description;
					ScrollContainer->AddChild(ItemWidget);
				}
			}
		}
	}
}
