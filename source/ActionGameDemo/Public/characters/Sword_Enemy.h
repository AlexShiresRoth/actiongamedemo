// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/EnemyAnimInstance.h"
#include "Characters/Regular_Enemy.h"
#include "Interfaces/IChargeAttack.h"
#include "Interfaces/UltimateAttack.h"
#include "Sword_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API ASword_Enemy : public ARegular_Enemy, public IUltimateAttack, public IIChargeAttack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* UltimateStartParticle;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* UltimateFinishParticle;

	UPROPERTY(EditAnywhere, Category = Particle)
	float UltimateAOERadius{400.f};

	UPROPERTY(EditAnywhere, Category = Particle)
	float UltimateAOEDamage{1000.f};

	UPROPERTY(EditAnywhere, Category = Particle)
	float LaunchVelocityMultiplier{3000.f};

	UPROPERTY(EditAnywhere, Category = Particle)
	float LaunchZ{300.f};

	UPROPERTY(EditAnywhere, Category = Ultimate)
	float UltimateCooldown{30.f};

	void SpawnAOECollision(FVector Location);
	void LaunchActorsInWake(AActor* HitActor) const;

	bool bCanUseUltimate{true};

public:
	UFUNCTION(BlueprintCallable)
	void StartUltimate();

	UFUNCTION(BlueprintCallable)
	void FinishUltimate();

	UFUNCTION(BlueprintCallable)
	void StartUltimateCooldown();

	UFUNCTION(BlueprintCallable)
	void FinishUltimateCooldown();

	UFUNCTION(BlueprintCallable)
	void DetectPlayer(class AActor* ActorDetected, class APawn* OtherPawn);

	virtual bool CanTakeDamage(AActor* Opponent, UDamageType* DamageType) override;
};
