// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Fighter.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatsComponent::ReduceHealth(const float Damage, AActor* Opponent, UDamageType* DamageType)
{
	IFighter* FighterRef{GetOwner<IFighter>()};

	if (!FighterRef->CanTakeDamage(Opponent, DamageType))
	{
		return;
	}

	Stats[Health] -= Damage;
	// Clamping will make sure that the health never goes below 0
	Stats[Health] = UKismetMathLibrary::FClamp(
		Stats[Health],
		0.0f,
		Stats[MaxHealth]);

	OnHealthPercentUpdateDelegate.Broadcast(GetStatPercentage(Health, MaxHealth));

	if (Stats[Health] <= 0)
	{
		OnZeroHealthDelegate.Broadcast();
	}
}

void UStatsComponent::AddHealth(const float HealAmt)
{
	if (Stats[Health] < Stats[MaxHealth])
	{
		Stats[Health] = UKismetMathLibrary::FClamp(
			Stats[Health] + HealAmt,
			0.f,
			Stats[MaxHealth]);
		OnHealthPercentUpdateDelegate.Broadcast(GetStatPercentage(Health, MaxHealth));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is max"));
	}
}

void UStatsComponent::ReduceStamina(float Amount)
{
	Stats[Stamina] -= Amount;

	Stats[Stamina] = UKismetMathLibrary::FClamp(
		Stats[Stamina],
		0.0f,
		Stats[MaxStamina]);

	bCanRegen = false;

	FLatentActionInfo FunctionInfo{
		0,
		100,
		TEXT("EnableRegen"),
		this
	};

	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		FunctionInfo);

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(Stamina, MaxStamina));
}

void UStatsComponent::RegenStamina()
{
	if (!bCanRegen)
	{
		return;
	}

	Stats[Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[Stamina],
		Stats[MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRegenRate);

	OnStaminaPercentUpdateDelegate.Broadcast(GetStatPercentage(Stamina, MaxStamina));
}

void UStatsComponent::EnableRegen()
{
	bCanRegen = true;
}

float UStatsComponent::GetStatPercentage(EStat Current, EStat Max)
{
	return Stats[Current] / Stats[Max];
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
