// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CompanionCharacter.h"

#include "StatsComponent.h"
#include "combat/CombatComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "PlayerCharacter.h"
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

	ACharacter* PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());


	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is null"));
		return;
	}

	if (PlayerRef)
	{
		BlackboardComp->SetValueAsObject("Player", PlayerRef);
		UE_LOG(LogTemp, Display, TEXT("Player value is %s"), *PlayerRef->GetName());
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

void ACompanionCharacter::DetectEnemy(class AActor* ActorDetected, class APawn* OtherPawn)
{
	// TODO handle detecting enemy and changing current state to attack state
	BlackboardComp->SetValueAsEnum("CurrentState", Companion_Range);
}
