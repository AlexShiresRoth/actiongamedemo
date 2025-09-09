// Fill out your copyright notice in the Description page of Project Settings.


#include "combat/CompanionProjectile.h"

#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
ACompanionProjectile::ACompanionProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACompanionProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACompanionProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACompanionProjectile::HandleBeginOverlap(AActor* OtherActor)
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

	UE_LOG(LogTemp, Warning, TEXT("Overlapping::%s"), *PawnRef->GetName());

	if (PawnRef->IsPlayerControlled())
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

void ACompanionProjectile::DestroyProjectile()
{
	Destroy();
}

void ACompanionProjectile::EndProjectileMovement(const float TimeDelay)
{
	FTimerHandle DeathTimerHandle{};

	FindComponentByClass<UParticleSystemComponent>()->SetTemplate(HitTemplate);
	FindComponentByClass<UProjectileMovementComponent>()->StopMovementImmediately();

	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACompanionProjectile::DestroyProjectile, TimeDelay);
}
