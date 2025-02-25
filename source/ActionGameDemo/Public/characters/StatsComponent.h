// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EStat.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnHealthPercentUpdateSignature,
	UStatsComponent, OnHealthPercentUpdateDelegate, float, Percent);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnStaminaPercentUpdateSignature,
	UStatsComponent, OnStaminaPercentUpdateDelegate, float, Percent);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnZeroHealthSignature,
	UStatsComponent, OnZeroHealthDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Stats")
	double StaminaRegenRate{10.0};

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	bool bCanRegen{true};

	UPROPERTY(EditAnywhere, Category = "Stats")
	float StaminaDelayDuration{2.0f};

public:
	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(EditAnywhere, Category = "Stats")
	TMap<TEnumAsByte<EStat>, float> Stats;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ReduceHealth(float Damage, AActor* Opponent);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ReduceStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RegenStamina();

	UFUNCTION()
	void EnableRegen();

	// Blueprintpure do not have execution pins and everything is read only within the function
	UFUNCTION(BlueprintPure)
	float GetStatPercentage(EStat Current, EStat Max);

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnHealthPercentUpdateSignature OnHealthPercentUpdateDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStaminaPercentUpdateSignature OnStaminaPercentUpdateDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnZeroHealthSignature OnZeroHealthDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
