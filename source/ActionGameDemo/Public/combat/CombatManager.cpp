// Fill out your copyright notice in the Description page of Project Settings.


#include "combat/CombatManager.h"

// Sets default values
ACombatManager::ACombatManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACombatManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACombatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACombatManager::UpdateCombatState()
{
	bool bShouldBeInCombat = CombatTargets.Num() > 0;

	if (bIsInCombat != bShouldBeInCombat)
	{
		bIsInCombat = bShouldBeInCombat;
		UE_LOG(LogTemp, Warning, TEXT("Player combat state changed: %s"),
		       bIsInCombat ? TEXT("IN COMBAT") : TEXT("OUT OF COMBAT"));
	}
}

void ACombatManager::AddCombatTarget(AActor* Target)
{
	if (Target != nullptr)
	{
		CombatTargets.Add(Target);
		UpdateCombatState();
	}
}

void ACombatManager::RemoveCombatTarget(AActor* Target)
{
	if (Target != nullptr)
	{
		CombatTargets.Remove(Target);
		UpdateCombatState();
	}
}
