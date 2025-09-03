// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CompanionCharacter.h"

#include "StatsComponent.h"
#include "combat/CombatComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "combat/CombatManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACompanionCharacter::ACompanionCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	// AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

// Called when the game starts or when spawned
void ACompanionCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIControllerRef = GetController<AAIController>();

	BlackboardComp = AIControllerRef->GetBlackboardComponent();

	ACharacter* PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));

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

	if (CombatManager)
	{
		if (CombatManager->bIsInCombat)
		{
			BlackboardComp->SetValueAsEnum("CurrentState", Companion_Range);
		}
		else
		{
			BlackboardComp->SetValueAsEnum("CurrentState", Companion_Following);
		}
	}
}

// Called to bind functionality to input
void ACompanionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
