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
#include "Animations/EnemyAnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/MainPlayer.h"
#include "Kismet/GameplayStatics.h"


ARegular_Enemy::ARegular_Enemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SetGenericTeamId(FGenericTeamId(TeamID));
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

	OriginalLocation = GetActorLocation();
	OriginalRotation = GetActorRotation();

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState);

	BlackboardComp->SetValueAsVector("StartLocation", OriginalLocation);
	BlackboardComp->SetValueAsRotator("StartRotation", OriginalRotation);

	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));

	GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>()->StatsComp->OnZeroHealthDelegate.AddDynamic(
		this,
		&ARegular_Enemy::HandlePlayerDeath);

	if (AIPerceptionComp)
	{
		AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ARegular_Enemy::OnTargetPerceptionUpdated);
	}
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

// TODO should we just handle this in BP?
void ARegular_Enemy::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor)
	{
		UE_LOG(LogTemp, Display, TEXT("OnTargetPerceptionUpdated actor: %s"), *Actor->GetName());
	}
}

void ARegular_Enemy::HandlePlayerDeath()
{
	ControllerRef->GetBlackboardComponent()->SetValueAsEnum(
		TEXT("CurrentState"),
		GameOver);
}


void ARegular_Enemy::DetectPlayer(class AActor* ActorDetected, class APawn* OtherPawn)
{
	if (bIsDead) { return; }

	EEnemyState CurrentState{
		static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
	};

	// TODO idk if we need this variable still
	bCanSeePlayer = true;


	const APawn* DetectedPawn = Cast<APawn>(ActorDetected);
	// detect only player
	if (DetectedPawn != OtherPawn)
	{
		return;
	}

	if (CombatManager != nullptr)
	{
		CombatManager->AddCombatTarget(ControllerRef->GetCharacter());
	}


	BlackboardComp->SetValueAsBool(TEXT("IsPlayerVisible"), true);

	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), Range);
}

void ARegular_Enemy::LosePlayer(AActor* LostActor)
{
	AActor* MainPlayer = GetWorld()->GetFirstPlayerController()->GetCharacter();

	if (bIsDead || LostActor != MainPlayer)
	{
		UE_LOG(LogTemp, Display, TEXT("LosePlayer::Enemy is either dead or character is companion::%s"),
		       *LostActor->GetName());
		return;
	}

	bCanSeePlayer = false;

	if (CombatManager != nullptr)
	{
		CombatManager->RemoveCombatTarget(ControllerRef->GetCharacter());
	}

	FTimerHandle VisibilityLossTimer;
	GetWorld()->GetTimerManager().SetTimer(
		VisibilityLossTimer,
		this,
		&ARegular_Enemy::HandleSetPlayerVisibility,
		.2f, // delay a bit
		false
	);
}

void ARegular_Enemy::HandleDeath()
{
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

	if (USkeletalMeshComponent* EnemyMesh = GetMesh())
	{
		if (UEnemyAnimInstance* EnemyAnim = Cast<UEnemyAnimInstance>(EnemyMesh->GetAnimInstance()))
		{
			EnemyAnim->bIsDead = true;
			UE_LOG(LogTemp, Display, TEXT("Dead"));
		}
	}

	if (CombatManager != nullptr)
	{
		CombatManager->RemoveCombatTarget(ControllerRef->GetCharacter());
	}

	FTimerHandle DestroyTimerHandle;
	// handle timer here
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ARegular_Enemy::FinishDeathAnim, 10,
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

void ARegular_Enemy::HandleSetPlayerVisibility()
{
	ControllerRef->ClearFocus(EAIFocusPriority::Gameplay);

	ControllerRef->StopMovement();

	BlackboardComp->SetValueAsBool(TEXT("IsPlayerVisible"), false);

	BlackboardComp->SetValueAsBool(TEXT("IsReadyToCharge"), false);
	// We can set return to start here and set idle in return to start task
	BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), ReturnToStart);
}


void ARegular_Enemy::FinishDeathAnim()
{
	Destroy();
}
