// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BossCharacter.h"
#include "combat/BlockComponent.h"
#include "Enums/FightStages.h"
#include "Interfaces/BlockAbility.h"
#include "Interfaces/IChargeAttack.h"
#include "Interfaces/UltimateAttack.h"
#include "SwordBoss.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API ASwordBoss : public ABossCharacter, public IUltimateAttack, public IIChargeAttack,
                                      public IBlockAbility
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	class UBlackboardComponent* BossBlackboardComponent;
	class AAIController* BossAI;

	bool bCanUseUltimate{false};


	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* UltimateStartParticle;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* UltimateFinishParticle;

	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem *RegenParticle;

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

public:
	ASwordBoss();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlockComponent* BlockComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
	TEnumAsByte<EFightStages> FightStage;

	// TODO - can we set this to array and play hurt anim based on where it's hit?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
	UAnimMontage* HurtMontage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = State)
	bool bIsInvulnerable{false};

	UFUNCTION(BlueprintCallable, Category = Boss)
	void PlayHurtAnimation();

	UFUNCTION(BlueprintCallable)
	void StartUltimate();

	UFUNCTION(BlueprintCallable)
	void FinishUltimate();

	UFUNCTION(BlueprintCallable)
	void StartUltimateCooldown();

	UFUNCTION(BlueprintCallable)
	void FinishUltimateCooldown();

	UFUNCTION(BlueprintCallable)
	void SpawnRegenParticle();

	UFUNCTION(BlueprintCallable)
	void CheckFightStage();

	virtual bool CanTakeDamage(AActor* Opponent, UDamageType* DamageType) override;
};
