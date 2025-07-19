// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Regular_Enemy.h"
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

// TODO figure out why damage is not happening on player
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

	BlackboardComp = GetController<AAIController>()->GetBlackboardComponent();

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState);

	ControllerRef = GetController<AAIController>();

	BlackboardComp = ControllerRef->GetBlackboardComponent();


	GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>()->StatsComp->OnZeroHealthDelegate.AddDynamic(
		this,
		&ARegular_Enemy::HandlePlayerDeath);
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

void ARegular_Enemy::HandlePlayerDeath()
{
	ControllerRef->GetBlackboardComponent()->SetValueAsEnum(
		TEXT("CurrentState"),
		GameOver);
}


void ARegular_Enemy::DetectPawn(class APawn* PawnDetected, class APawn* OtherPawn)
{
	EEnemyState CurrentState{
		static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
	};

	// detect only player
	if (PawnDetected != OtherPawn || CurrentState != Idle) { return; }

	UE_LOG(LogTemp, Display, TEXT("Pawn Detected"));

	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), Range);
}

void ARegular_Enemy::HandleDeath()
{
	float Duration{PlayAnimMontage(DeathAnim)};

	ControllerRef->GetBrainComponent()->StopLogic("defeated");

	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle DestroyTimerHandle;
	// handle timer here
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ARegular_Enemy::FinishDeathAnim, Duration * 100,
	                                       false);

	IMainPlayer* PlayerRef{
		GetWorld()->GetFirstPlayerController()->GetPawn<IMainPlayer>()
	};

	if (!PlayerRef)
	{
		return;
	}

	PlayerRef->EndLockonWithActor(this);
}

float ARegular_Enemy::GetMeleeRange()
{
	return StatsComp->Stats[MeleeRange];
}

float ARegular_Enemy::GetDamage()
{
	return StatsComp->Stats[Strength];
}

void ARegular_Enemy::Attack()
{
	CombatComp->RandomAttack();
}

float ARegular_Enemy::GetAnimDuration()
{
	return CombatComp->AnimDuration;
}

void ARegular_Enemy::FinishDeathAnim()
{
	Destroy();
}
