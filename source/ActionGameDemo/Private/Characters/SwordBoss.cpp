// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SwordBoss.h"

#include "AIController.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/PlayerCharacter.h"
#include "DamageTypes/UnblockableDamage.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Structs/FAttackData.h"

// TODO - need a parent anim instance,to share setisblocking
void ASwordBoss::BeginPlay()
{
	Super::BeginPlay();

	AAIController* AIController = Cast<AAIController>(GetController());
	BossBlackboardComponent = AIController->GetBlackboardComponent();

	if (BossBlackboardComponent)
	{
		BossBlackboardComponent->SetValueAsEnum("FightStages", FightStage);
	}
}

void ASwordBoss::SpawnAOECollision(FVector Location)
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

void ASwordBoss::LaunchActorsInWake(AActor* HitActor) const
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

ASwordBoss::ASwordBoss()
{
	if (ControllerRef)
	{
		BossBlackboardComponent = ControllerRef->GetBlackboardComponent();
	}

	BlockComponent = CreateDefaultSubobject<UBlockComponent>(TEXT("BlockComponent"));
}

void ASwordBoss::PlayHurtAnimation()
{
	if (!HurtMontage || bIsDead) { return; }

	float AnimDuration{PlayAnimMontage(HurtMontage)};
}

void ASwordBoss::StartUltimate()
{
	if (UltimateStartParticle)
	{
		ACharacter* EnemyRef = ControllerRef->GetCharacter();
		FVector Loc = EnemyRef->GetActorLocation();
		FRotator Rotator = EnemyRef->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), UltimateStartParticle, Loc, Rotator);
	}
}

void ASwordBoss::FinishUltimate()
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

void ASwordBoss::StartUltimateCooldown()
{
	bCanUseUltimate = false;

	if (BossBlackboardComponent)
	{
		BossBlackboardComponent->SetValueAsBool("CanUseUltimate", false);
	}

	if (!ControllerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASwordBoss::StartUltimateCooldown — ControllerRef is null"));
		return;
	}

	ACharacter* EnemyRef = ControllerRef->GetCharacter();
	if (!EnemyRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASwordBoss::StartUltimateCooldown — EnemyRef is null"));
		return;
	}

	USkeletalMeshComponent* EnemyMesh = EnemyRef->GetMesh();
	if (!EnemyMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASwordBoss::StartUltimateCooldown — EnemyMesh is null"));
		return;
	}

	UAnimInstance* AnimInstance = EnemyMesh->GetAnimInstance();
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASwordBoss::StartUltimateCooldown — AnimInstance is null"));
		return;
	}

	if (UBossAnimInstance* BossAnim = Cast<UBossAnimInstance>(AnimInstance))
	{
		Execute_SetIsUltimateState(BossAnim, false);
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(
		TimerHandle,
		this,
		&ASwordBoss::FinishUltimateCooldown,
		UltimateCooldown,
		false
	);
}


void ASwordBoss::FinishUltimateCooldown()
{
	bCanUseUltimate = true;
	BossBlackboardComponent->SetValueAsBool("CanUseUltimate", true);
}

bool ASwordBoss::CanTakeDamage(AActor* Opponent, UDamageType* DamageType)
{
	if (USkeletalMeshComponent* BossMesh = ControllerRef->GetCharacter()->GetMesh())
	{
		if (BossMesh)
		{
			if (BossMesh->GetAnimInstance())
			{
				if (UBossAnimInstance* BossAnim = Cast<UBossAnimInstance>(BossMesh->GetAnimInstance()))
				{
					if (BossAnim->GetIsBlocking())
					{
						if (BlockComponent->CheckEnemy(Opponent))
						{
							CharacterAudioComp->PlayDamageAudio();
							return true;
						}
						CharacterAudioComp->PlayBlockAudio();
						return false;
					}
				}
			}
		}
	}
	return true;
}
