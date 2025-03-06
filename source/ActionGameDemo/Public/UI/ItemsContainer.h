// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "ItemsContainer.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetClosed);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnRemoveItemFromObjectSignature,
	UItemsContainer,
	OnRemoveItemFromObjectDelegate,
	class AItem *,
	ItemToRemove);

UCLASS()
class ACTIONGAMEDEMO_API UItemsContainer : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollContainer;

	TArray<class AItem*> ItemsList;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UItemWidget> ItemWidgetClass;

	UFUNCTION(BlueprintCallable)
	void SetItems(TArray<class AItem*> Items);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnWidgetClosed OnWidgetClosed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnRemoveItemFromObjectSignature OnRemoveItemFromObjectDelegate;

	UFUNCTION(BlueprintCallable)
	void CLoseWidget();

	void SetContainerTitle(FString NewTitle);

	UFUNCTION()
	void RemoveItemFromContainer(const FText ItemID);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
