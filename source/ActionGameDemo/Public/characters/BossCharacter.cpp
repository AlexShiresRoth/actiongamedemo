// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsComponent.h"
#include "EStat.h"
#include "combat/CombatComponent.h"
#include "combat/TraceComponent.h"
#include "combat/BlockComponent.h"
#include "PlayerActionsComponent.h"
#include "characters/BossCharacter.h"

// Sets default values
ABossCharacter::ABossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
}

void ABossCharacter::DetectPawn(class APawn *PawnDetected, class APawn *OtherPawn)
{
	if (PawnDetected != OtherPawn)
	{
		return;
	};

	UE_LOG(LogTemp, Warning, TEXT("Pawn Detected %s"), *PawnDetected->GetName());
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
