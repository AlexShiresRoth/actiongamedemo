// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "IDetailTreeNode.h"
#include "combat/EquipmentComponent.h"
#include "Interactable/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInventoryComponent::AddItemToInventory(class AItem* Item)
{
	if (InventoryItems.Contains(Item))
	{
		// Increase the number of same item?
	}
	if (Item->ItemData.ItemTypeMacro == Consumable)
	{
		InventoryItems.Add(Item);
	}
	if (Item->ItemData.ItemTypeMacro == Equipable)
	{
		EquipmentItems.Add(Item);
	}
}

void UInventoryComponent::AddEquippedItems(TEnumAsByte<EEQuipmentSlot> SlotKey, FItemData ItemData)
{
	if (ItemData.ID.IsEmpty())
	{
		return;
	}

	EquippedItems.Add(SlotKey, ItemData);

	UEquipmentComponent* EquipmentComp = GetOwner()->FindComponentByClass<UEquipmentComponent>();
	if (EquipmentComp)
	{
		EquipmentComp->Equipment.Add(SlotKey, ItemData);

		for (const auto& Pair : EquippedItems)
		{
			FString SlotName = UEnum::GetValueAsString(Pair.Key);
			FString ItemID = Pair.Value.ID; // Assuming FItemData has an ID field
			UE_LOG(LogTemp, Warning, TEXT("Equipped -> Slot: %s | Item: %s"), *SlotName, *ItemID);
		}
	}
}
