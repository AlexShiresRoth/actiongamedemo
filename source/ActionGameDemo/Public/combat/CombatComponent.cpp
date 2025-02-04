// Fill out your copyright notice in the Description page of Project Settings.

#include "combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCombatComponent::ComboAttack()
{
	CharacterRef->PlayAnimMontage(AttackAnimations[ComboCounter]);
	ComboCounter++;

	int MaxCombo{AttackAnimations.Num()};

	// when wrapping around, the lib increments by 1 so setting it at -1 will make it 0 when wrapping
	ComboCounter = UKismetMathLibrary::Wrap(ComboCounter, -1, MaxCombo - 1);
}

// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
}

// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
