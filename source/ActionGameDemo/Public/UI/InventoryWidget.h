// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ItemsContainer;

	APlayerController* PC;
	ACharacter* CharacterRef;
	AActor* PlayerRef;

public:
	UPROPERTY()
	class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class AItem*> InventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UItemWidget> ItemWidgetClass;

	UFUNCTION(BlueprintCallable)
	void CLoseInventoryWidget();
};
