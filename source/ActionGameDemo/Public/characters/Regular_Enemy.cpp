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
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HLSLTree/HLSLTreeEmit.h"
#include "Interfaces/MainPlayer.h"


ARegular_Enemy::ARegular_Enemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

void ARegular_Enemy::PlayHurtAnimation()
{
	if (!HurtAnimMontage || bIsDead) { return; }

	float AnimDuration{PlayAnimMontage(HurtAnimMontage)};
}

void ARegular_Enemy::Knockback(AActor* Attacker)
{
	if (bIsDead) { return; }
	if (!Attacker) { return; }
	ACharacter* EnemyRef = ControllerRef->GetCharacter();
	if (!EnemyRef) { return; }

	FVector KnockbackDirection = EnemyRef->GetActorLocation() - Attacker->GetActorLocation();
	KnockbackDirection.Z = 0.f;
	KnockbackDirection.Normalize();

	float KnockbackStrength = 600.f; // TODO might want to make this a uprop

	FVector LaunchVelocity = KnockbackDirection * KnockbackStrength + FVector(0, 0, 250);

	EnemyRef->LaunchCharacter(LaunchVelocity, true, true);
}

// Called when the game starts or when spawned
void ARegular_Enemy::BeginPlay()
{
	Super::BeginPlay();


	ControllerRef = GetController<AAIController>();

	BlackboardComp = ControllerRef->GetBlackboardComponent();

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState);


	BlackboardComp = ControllerRef->GetBlackboardComponent();

	GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>()->StatsComp->OnZeroHealthDelegate.AddDynamic(
		this,
		&ARegular_Enemy::HandlePlayerDeath);
}

// Called every frame
void ARegular_Enemy::Tick(float DeltaTime)
{
	if (bIsDead) { return; }
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
	if (bIsDead) { return; }

	EEnemyState CurrentState{
		static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
	};

	// detect only player
	if (PawnDetected != OtherPawn || CurrentState != Idle) { return; }


	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), Range);
}

void ARegular_Enemy::HandleDeath()
{
	float Duration{PlayAnimMontage(DeathAnim)};

	bIsDead = true;

	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), Death);

	ControllerRef->StopMovement();

	ControllerRef->GetBrainComponent()->StopLogic("defeated");

	ControllerRef->ClearFocus(EAIFocusPriority::Gameplay);


	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(ControllerRef->BrainComponent))
	{
		// @note - Editor may still show enemy bt is running
		BTComp->StopTree(EBTStopMode::Forced);
	}

	HandleDisableCollisionOnDeath();

	FTimerHandle DestroyTimerHandle;
	// handle timer here
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ARegular_Enemy::FinishDeathAnim, Duration * 50,
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

bool ARegular_Enemy::IsDead_Implementation() const
{
	return bIsDead;
}

void ARegular_Enemy::HandleDisableCollisionOnDeath()
{
	FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void ARegular_Enemy::FinishDeathAnim()
{
	Destroy();
}
