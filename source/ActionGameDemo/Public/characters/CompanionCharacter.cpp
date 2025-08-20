// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CompanionCharacter.h"

#include "StatsComponent.h"
#include "combat/CombatComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ACompanionCharacter::ACompanionCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

// Called when the game starts or when spawned
void ACompanionCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIControllerRef = GetController<AAIController>();

	BlackboardComp = AIControllerRef->GetBlackboardComponent();

	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is null"));
		return;
	}

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState);
}

// Called every frame
void ACompanionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACompanionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
