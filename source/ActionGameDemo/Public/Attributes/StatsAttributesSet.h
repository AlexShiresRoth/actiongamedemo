// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "StatsAttributesSet.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UStatsAttributesSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UStatsAttributesSet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldVal);
};
