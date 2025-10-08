// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "UI/ItemWidget.h"
#include "Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Characters/StatsComponent.h"
#include "combat/EquipmentComponent.h"
#include "Interactable/Item.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PC = GetWorld()->GetFirstPlayerController();
	CharacterRef = PC->GetCharacter();
	PlayerRef = Cast<AActor>(CharacterRef);

	if (PC && PlayerRef)
	{
		InventoryComponent = PlayerRef->FindComponentByClass<UInventoryComponent>();
		EquipmentComponent = PlayerRef->FindComponentByClass<UEquipmentComponent>();

		if (InventoryComponent)
		{
			// PC->bShowMouseCursor = true;
			// TODO figure out how to allow toggling inventory and showing mouse cursor can work
			// PC->SetInputMode(FInputModeUIOnly());
			// Get items stored on user inventory in order to create widgets
			InventoryItems = InventoryComponent->GetInventoryItems();
			EquipmentItems = InventoryComponent->GetEquipmentItems();

			// Items will show in different inventory areas based on their type
			RenderItemsToWidget(ItemsContainer, InventoryItems);
			RenderItemsToWidget(EquipmentContainer, EquipmentItems);
		}

		if (EquipmentComponent)
		{
			FItemData* Sword = EquipmentComponent->Equipment.Find(EEQuipmentSlot::Sword);
			FItemData* Armor = EquipmentComponent->Equipment.Find(EEQuipmentSlot::Armor);
			FItemData* Shield = EquipmentComponent->Equipment.Find(EEQuipmentSlot::Shield);
			FItemData* Special = EquipmentComponent->Equipment.Find(EEQuipmentSlot::Special);

			if (Sword)
			{
				EquippedSword = *Sword;
			}
			if (Armor)
			{
				EquippedArmor = *Armor;
			}
			if (Shield)
			{
				EquippedShield = *Shield;
			}
			if (Special)
			{
				EquippedSpecial = *Special;
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

void UInventoryWidget::RenderItemsToWidget(UScrollBox* Container, TArray<AItem*>& Items)
{
	if (Items.Num() > 0)
	{
		for (const AItem* Item : Items)
		{
			if (Container)
			{
				if (UItemWidget* ItemWidget = CreateWidget<UItemWidget>(this, ItemWidgetClass))
				{
					ItemWidget->ItemLocation = Inventory;
					ItemWidget->ItemData = Item->ItemData;
					ItemWidget->OnItemActionsMenuDelegate.
					            AddDynamic(this, &UInventoryWidget::HandleItemActions);
					Container->AddChild(ItemWidget);
					ItemWidgets.Add(ItemWidget);
				}
			}
		}
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


void UInventoryWidget::EquipItem(FItemData Item)
{
	if (Item.ID.IsEmpty())
	{
		return;
	}

	EquippedItems.Add(Item.TypePair.ItemType, Item);

	switch (Item.TypePair.ItemType)
	{
	case ArmorType:
		InventoryComponent->AddEquippedItems(Armor, Item);
		EquippedArmor = Item;
		break;
	case WeaponType:
		InventoryComponent->AddEquippedItems(Sword, Item);
		EquippedSword = Item;
		break;
	case ShieldType:
		InventoryComponent->AddEquippedItems(Shield, Item);
		EquippedShield = Item;
		break;
	case SpecialType:
		InventoryComponent->AddEquippedItems(Special, Item);
		EquippedSpecial = Item;
		break;
	default:
		break;
	}
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
