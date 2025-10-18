// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Sword_Enemy.h"
#include "Engine/DamageEvents.h"
#include "AIController.h"
#include "Animations/EnemyAnimInstance.h"
#include "Characters/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DamageTypes/UnblockableDamage.h"
#include "Kismet/GameplayStatics.h"

void ASword_Enemy::SpawnAOECollision(FVector Location)
{
	TArray<FOverlapResult> Overlaps;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(UltimateAOERadius);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	bool bHit = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Location,
		FQuat::Identity,
		ECC_Pawn,
		Sphere,
		QueryParams
	);

	if (bHit)
	{
		for (const auto& Res : Overlaps)
		{
			AActor* HitActor = Res.GetActor();
			if (HitActor && HitActor != this)
			{
				HitActor->TakeDamage(
					UltimateAOEDamage,
					FDamageEvent(UUnblockableDamage::StaticClass()),
					this->GetInstigatorController(),
					this
				);

				LaunchActorsInWake(HitActor);
			}
		}
	}
}

void ASword_Enemy::LaunchActorsInWake(AActor* HitActor) const
{
	if (ACharacter* HitChar = Cast<ACharacter>(HitActor))
	{
		FVector LaunchDirection = (HitChar->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector LaunchVelocity = LaunchDirection * LaunchVelocityMultiplier;
		LaunchVelocity.Z = LaunchZ;


		FAttackData HitData{
			GetOwner(),
			LaunchVelocity,
		};

		if (APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(HitChar))
		{
			PlayerChar->ReceiveHitFromAOE(HitData);
		}
	}
}

void ASword_Enemy::StartUltimate()
{
	if (UltimateStartParticle)
	{
		ACharacter* EnemyRef = ControllerRef->GetCharacter();
		FVector Loc = EnemyRef->GetActorLocation();
		FRotator Rotator = EnemyRef->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UltimateStartParticle, Loc, Rotator);
	}
}

void ASword_Enemy::FinishUltimate()
{
	if (UltimateFinishParticle)
	{
		ACharacter* EnemyRef = ControllerRef->GetCharacter();
		FVector Loc = EnemyRef->GetActorLocation();
		FRotator Rotator = EnemyRef->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UltimateFinishParticle, Loc, Rotator);

		SpawnAOECollision(Loc);
	}
}

void ASword_Enemy::StartUltimateCooldown()
{
	ACharacter* EnemyRef = ControllerRef->GetCharacter();
	USkeletalMeshComponent* EnemyMesh = EnemyRef->GetMesh();
	UAnimInstance* AnimInstance = EnemyMesh->GetAnimInstance();

	if (!EnemyMesh || !AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASWORD_ENEMY::This should not happen, something is broken"));
		return;
	}

	if (UEnemyAnimInstance* EnemyAnim = Cast<UEnemyAnimInstance>(AnimInstance))
	{
		EnemyAnim->SetIsUltimateState(false);
	}

	bCanUseUltimate = false;

	BlackboardComp->SetValueAsBool("CanUseUltimate", false);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ASword_Enemy::FinishUltimateCooldown,
		UltimateCooldown,
		false
	);
}

void ASword_Enemy::FinishUltimateCooldown()
{
	bCanUseUltimate = true;
	BlackboardComp->SetValueAsBool("CanUseUltimate", true);
}


void ASword_Enemy::DetectPlayer(class AActor* ActorDetected, class APawn* OtherPawn)
{
	const APawn* DetectedPawn = Cast<APawn>(ActorDetected);
	const AActor* MainPlayer = GetWorld()->GetFirstPlayerController()->GetCharacter();
	// detect only player
	if (DetectedPawn != OtherPawn)
	{
		return;
	}
	if (bIsDead || DetectedPawn != MainPlayer) { return; }

	if (BlackboardComp)
	{
		EEnemyState CurrentState{
			static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
		};

		// TODO idk if we need this variable still
		bCanSeePlayer = true;

		if (CombatManager)
		{
			CombatManager->AddCombatTarget(ControllerRef->GetCharacter());
		}

		BlackboardComp->SetValueAsBool(TEXT("IsPlayerVisible"), true);

		BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), Charge);
	}
}

bool ASword_Enemy::CanTakeDamage(AActor* Opponent, UDamageType* DamageType)
{
	// TODO this needs refactor-there might be an anim instance on the enemy already and this is just extra
	// TODO we also need to make blocking less active
	// TODO need a block impact particle hit
	// TODO and a combo attack
	if (USkeletalMeshComponent* EnemyMesh = ControllerRef->GetCharacter()->GetMesh())
	{
		if (EnemyMesh)
		{
			if (EnemyMesh->GetAnimInstance())
			{
				if (UEnemyAnimInstance* EnemyAnim = Cast<UEnemyAnimInstance>(EnemyMesh->GetAnimInstance()))
				{
					if (EnemyAnim->GetIsBlocking())
					{
						// TODO need to set up a check for block component like on main player but for enemies
						return false;
					}
				}
			}
		}
	}
	return true;
}
