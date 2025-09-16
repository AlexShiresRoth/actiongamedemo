// Fill out your copyright notice in the Description page of Project Settings.

#include "BossCharacter.h"
#include "StatsComponent.h"
#include "EStat.h"
#include "combat/CombatComponent.h"
#include "combat/TraceComponent.h"
#include "combat/BlockComponent.h"
#include "PlayerActionsComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/MainPlayer.h"
#include "Kismet/GameplayStatics.h"

// TODO need to handle lost sight of player for Boss
// Sets default values
ABossCharacter::ABossCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	ControllerRef = GetController<AAIController>();

	BlackboardComp = ControllerRef->GetBlackboardComponent();

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState);

	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));

	GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>()->StatsComp->OnZeroHealthDelegate.AddDynamic(
		this,
		&ABossCharacter::HandlePlayerDeath);
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABossCharacter::DetectPawn(class APawn* PawnDetected, class APawn* OtherPawn)
{
	EEnemyState CurrentState{
		static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(
			TEXT("CurrentState")))
	};

	if (PawnDetected != OtherPawn || CurrentState != Idle)
	{
		return;
	}

	if (CombatManager)
	{
		CombatManager->AddCombatTarget(ControllerRef->GetCharacter());
	}

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		Range);
}

float ABossCharacter::GetDamage()
{
	return StatsComp->Stats[Strength];
}

void ABossCharacter::Attack()
{
	CombatComp->RandomAttack();
}

float ABossCharacter::GetAnimDuration()
{
	return CombatComp->AnimDuration;
}

float ABossCharacter::GetMeleeRange()
{
	return StatsComp->Stats[MeleeRange];
}

void ABossCharacter::HandlePlayerDeath()
{
	ControllerRef->GetBlackboardComponent()->SetValueAsEnum(
		TEXT("CurrentState"),
		GameOver);
}

void ABossCharacter::HandleDeath()
{
	float Duration{PlayAnimMontage(DeathAnim)};

	ControllerRef->GetBrainComponent()->StopLogic("defeated");

	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DestroyTimerHandle;
	// handle timer here
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ABossCharacter::FinishDeathAnim, Duration * 100,
	                                       false);

	IMainPlayer* PlayerRef{
		GetWorld()->GetFirstPlayerController()->GetPawn<IMainPlayer>()
	};

	if (CombatManager)
	{
		CombatManager->RemoveCombatTarget(ControllerRef->GetCharacter());
	}

	if (!PlayerRef)
	{
		return;
	}

	PlayerRef->EndLockonWithActor(this);

	bIsDead = true;
}

void ABossCharacter::FinishDeathAnim()
{
	Destroy();
}
