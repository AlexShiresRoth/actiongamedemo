// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "Characters/InventoryComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Interactable/Item.h"

// TODO this works, but if I have my inventory item while adding items from a container, it doesn't get updated
void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterRef = GetWorld()->GetFirstPlayerController()->GetCharacter();
	PlayerRef = Cast<AActor>(CharacterRef);

	if (PlayerRef)
	{
		InventoryComponent = PlayerRef->FindComponentByClass<UInventoryComponent>();

		if (InventoryComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *InventoryComponent->GetName());
			InventoryItems = InventoryComponent->GetInventoryItems();
			if (InventoryItems.Num() > 0)
			{
				for (const AItem* Item : InventoryItems)
				{
					UE_LOG(LogTemp, Warning, TEXT("Item %s"), *Item->GetName());
				}
			}
		}
	}
}

void UInventoryWidget::SetInventoryItems()
{
	if (InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory component set"));
	}
}
