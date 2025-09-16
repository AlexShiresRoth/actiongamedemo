// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/EEQuipmentSlot.h"
#include "UI/InventoryWidget.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere)
	TArray<class AItem*> InventoryItems;

	UPROPERTY(EditAnywhere)
	TArray<class AItem*> EquipmentItems;

	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EEQuipmentSlot>, FItemData> EquippedItems;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UInventoryWidget> InventoryWidgetClass;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(class AItem* Item);

	UFUNCTION(BlueprintCallable)
	TArray<AItem*> GetInventoryItems() { return InventoryItems; };

	UFUNCTION(BlueprintCallable)
	TArray<AItem*> GetEquipmentItems() { return EquipmentItems; };
};
