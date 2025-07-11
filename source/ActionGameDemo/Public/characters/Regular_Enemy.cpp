// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Regular_Enemy.h"

#include "StatsComponent.h"
#include "combat/CombatComponent.h"

// Sets default values
ARegular_Enemy::ARegular_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

}

// Called when the game starts or when spawned
void ARegular_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARegular_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARegular_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARegular_Enemy::DetectPawn(class APawn* PawnDetected, class APawn* OtherPawn)
{
	if (PawnDetected == OtherPawn)
	{
		UE_LOG(LogTemp, Display, TEXT("Pawn Detected"));
	}
}



