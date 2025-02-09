// Fill out your copyright notice in the Description page of Project Settings.
#include "StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatsComponent::ReduceHealth(float Damage)
{
	if (Stats[EStat::Health] <= 0)
	{
		return;
	};

	Stats[EStat::Health] -= Damage;
	// Clamping will make sure that the health never goes below 0
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(
		Stats[EStat::Health],
		0.0f,
		Stats[EStat::MaxHealth]);
}

void UStatsComponent::ReduceStamina(float Amount)
{
	Stats[EStat::Stamina] -= Amount;

	Stats[EStat::Stamina] = UKismetMathLibrary::FClamp(
		Stats[EStat::Stamina],
		0.0f,
		Stats[EStat::MaxStamina]);

	bCanRegen = false;

	FLatentActionInfo FunctionInfo{
		0,
		100,
		TEXT("EnableRegen"),
		this};

	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		FunctionInfo);
}

void UStatsComponent::RegenStamina()
{

	if (!bCanRegen)
	{
		return;
	}

	Stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina],
		Stats[EStat::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRegenRate);
}

void UStatsComponent::EnableRegen()
{
	bCanRegen = true;
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
