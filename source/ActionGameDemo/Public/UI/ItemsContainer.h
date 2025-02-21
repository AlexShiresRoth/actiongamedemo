// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "ItemsContainer.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UItemsContainer : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollContainer;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UItemWidget> ItemWidgetClass;

	UFUNCTION(BlueprintCallable)
	void SetItems(TArray<class AItem*> Items);
};
