// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EStat.h"
#include "StatsComponent.generated.h"

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
	void ReduceHealth(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void ReduceStamina(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void RegenStamina();

	UFUNCTION()
	void EnableRegen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
