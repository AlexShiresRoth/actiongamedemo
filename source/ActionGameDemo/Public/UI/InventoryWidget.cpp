// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "ItemWidget.h"
#include "Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/StatsComponent.h"
#include "Interactable/Item.h"

// TODO refactor this function
// TODO Items in the inventory should have different functionality than that in an items container
// Weshould probably pop up a menu when clicking on an item
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PC = GetWorld()->GetFirstPlayerController();
	CharacterRef = PC->GetCharacter();
	PlayerRef = Cast<AActor>(CharacterRef);

	if (PC && PlayerRef)
	{
		InventoryComponent = PlayerRef->FindComponentByClass<UInventoryComponent>();

		if (InventoryComponent)
		{
			// PC->bShowMouseCursor = true;
			// TODO figure out how to allow toggling inventory and showing mouse cursor can work
			// PC->SetInputMode(FInputModeUIOnly());
			// Get items stored on user inventory in order to create widgets
			InventoryItems = InventoryComponent->GetInventoryItems();

			if (InventoryItems.Num() > 0)
			{
				for (const AItem* Item : InventoryItems)
				{
					if (ItemsContainer)
					{
						if (UItemWidget* ItemWidget = CreateWidget<UItemWidget>(this, ItemWidgetClass))
						{
							ItemWidget->ItemLocation = Inventory;
							ItemWidget->ItemData = Item->ItemData;
							ItemWidget->OnItemActionsMenuDelegate.
							            AddDynamic(this, &UInventoryWidget::HandleItemActions);
							ItemsContainer->AddChild(ItemWidget);
							ItemWidgets.Add(ItemWidget);
						}
					}
				}
			}
		}
	}
}

void UInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void UInventoryWidget::CLoseInventoryWidget()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		if (APlayerCharacter* Character = Cast<APlayerCharacter>(PC->GetPawn()))
		{
			Character->RestoreGameInput();
			this->RemoveFromParent();
		}
	}
}

void UInventoryWidget::HandleItemActions(FItemData Item)
{
	if (Item.ID.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Actions delegate::Missing Item Data"));
		return;
	}

	SelectedItem = Item;
	SelectedItemCategory = UEnum::GetValueAsString(Item.TypePair.ItemType.GetValue());
}

void UInventoryWidget::UseItem(FItemData Item)
{
	if (Item.ID.IsEmpty())
	{
		return;
	}
	switch (Item.TypePair.ItemType)
	{
	case Healing:
		if (UStatsComponent* StatsComp = PlayerRef->FindComponentByClass<UStatsComponent>())
		{
			// apply the affect to the character
			StatsComp->AddHealth(Item.TypePair.TypeValue);

			InventoryItems.RemoveAll([&](AItem* InventoryItem)
			{
				return InventoryItem && InventoryItem->ItemData.ID == Item.ID;
			});

			InventoryComponent->InventoryItems = InventoryItems;
			// Reset selected Item
			SelectedItem = FItemData();

			// Remove the widget associated with the id
			for (int32 i = ItemWidgets.Num() - 1; i >= 0; i--)
			{
				if (ItemWidgets[i] && ItemWidgets[i]->ItemData.ID.Equals(Item.ID))
				{
					ItemWidgets[i]->RemoveFromParent();
					ItemWidgets.RemoveAt(i);
				}
			}
		}

		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Item Is not a Healing type::UseItem"));
	}
	// 4. remove the item from the inventory
}
