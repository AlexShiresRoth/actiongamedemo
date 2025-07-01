// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "ItemWidget.h"
#include "Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
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
							ItemWidget->ItemName = FText::FromName(Item->ItemData.Name);
							ItemWidget->ItemID = FText::FromName(Item->ItemData.ID);
							ItemWidget->ItemIcon = Item->ItemData.ItemIcon;
							ItemWidget->Description = Item->ItemData.Description;

							ItemsContainer->AddChild(ItemWidget);
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
