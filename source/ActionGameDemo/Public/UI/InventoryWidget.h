// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Enums/EEQuipmentSlot.h"
#include "Interactable/Item.h"
#include "Structs/ItemData.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */


UCLASS(BlueprintType, Blueprintable)
class ACTIONGAMEDEMO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ItemsContainer;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* EquipmentContainer;

	APlayerController* PC;
	ACharacter* CharacterRef;
	AActor* PlayerRef;

protected:
	void RenderItemsToWidget(UScrollBox* Container, TArray<AItem*>& Items);

public:
	UPROPERTY()
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class AItem*> InventoryItems;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class AItem*> EquipmentItems;

	UPROPERTY(VisibleAnywhere)
	TArray<class UItemWidget*> ItemWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<TEnumAsByte<EItemTypes>, FItemData> EquippedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UItemWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemData SelectedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SelectedItemCategory;

	UFUNCTION(BlueprintCallable)
	void CLoseInventoryWidget();

	UFUNCTION()
	void HandleItemActions(FItemData Item);

	UFUNCTION(BlueprintCallable)
	void EquipItem(FItemData Item);

	UFUNCTION(BlueprintCallable)
	void UseItem(FItemData Item);

	UFUNCTION(BlueprintCallable)
	void ResetSelectedItem() { SelectedItem = FItemData(); }
};
