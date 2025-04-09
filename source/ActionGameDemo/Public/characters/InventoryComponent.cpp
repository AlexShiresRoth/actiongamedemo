// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

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

	// ...
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
	UE_LOG(LogTemp, Display, TEXT("Adding item to inventory %s"), *Item->GetName());
	if (InventoryItems.Contains(Item))
	{
		// Increase the number of same item?
	}
	if (!InventoryItems.Contains(Item))
	{
		InventoryItems.Add(Item);
	}
}
