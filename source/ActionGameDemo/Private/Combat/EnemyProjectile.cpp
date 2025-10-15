// Fill out your copyright notice in the Description page of Project Settings.

#include "combat/EnemyProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TODO I think there's an issue when the projectile overlaps either the water or interactable actor
void AEnemyProjectile::HandleBeginOverlap(AActor* OtherActor)
{
	APawn* PawnRef{
		Cast<APawn>(OtherActor)
	};
	// If hitting static object just destroy projectile
	if (!PawnRef)
	{
		EndProjectileMovement(2.f);
		return;
	}

	if (!PawnRef->IsPlayerControlled())
	{
		return;
	}
	
	EndProjectileMovement(.5f);

	FindComponentByClass<USphereComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FDamageEvent ProjectileAttackEvent{};

	PawnRef->TakeDamage(
		ProjectileDamage,
		ProjectileAttackEvent,
		PawnRef->GetController(),
		this);
}

void AEnemyProjectile::DestroyProjectile()
{
	Destroy();
}

void AEnemyProjectile::EndProjectileMovement(const float TimeDelay)
{
	FTimerHandle DeathTimerHandle{};

	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();

	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEnemyProjectile::DestroyProjectile, TimeDelay);
}
