// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemsContainer.h"

#include "IDetailTreeNode.h"
#include "ItemWidget.h"
#include "Interactable/Item.h"


//TODO may have to broadcast the remove event from here to interactable actor to remove from that list as well
void UItemsContainer::SetItems(TArray<class AItem*> Items)
{
	if (!ScrollContainer || !IsValid(ItemWidgetClass))
	{
		UE_LOG(LogTemp, Error, TEXT("UITEMSCONTAINER::Scrollcontainer or ItemWidgetClass is null"));
		return;
	}

	if (Items.Num() > 0)
	{
		ItemsList = Items;

		for (AItem* Item : Items)
		{
			if (Item)
			{
				if (UItemWidget* ItemWidget = CreateWidget<UItemWidget>(this, ItemWidgetClass))
				{
					ItemWidget->OnAddItemToInventoryDelegate.
					            AddDynamic(this, &UItemsContainer::RemoveItemFromContainer);
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

void UItemsContainer::RemoveItemFromContainer(const FText ItemID)
{
	for (int32 i = 0; i < ItemsList.Num(); i++)
	{
		if (ItemsList[i]->ItemData.ID.ToString() == ItemID.ToString())
		{
			return OnRemoveItemFromObjectDelegate.Broadcast(ItemsList[i]);
		}
	}
}

void UItemsContainer::CLoseWidget()
{
	OnWidgetClosed.Broadcast();
	RemoveFromParent();
}

void UItemsContainer::SetContainerTitle(FString NewTitle)
{
	if (NewTitle == "")
	{
		Title = FString("Needs title");
		return;
	}

	Title = NewTitle;
}

// TODO should we move this to playercontroller?
void UItemsContainer::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}

void UItemsContainer::NativeDestruct()
{
	Super::NativeDestruct();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}
