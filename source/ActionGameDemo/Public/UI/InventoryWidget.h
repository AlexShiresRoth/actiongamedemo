// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	ACharacter* CharacterRef;
	AActor* PlayerRef;

public:
	UPROPERTY()
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class AItem*> InventoryItems;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetInventoryItems();
};
