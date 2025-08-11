// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EEnemyState.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Interfaces/Fighter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Regular_Enemy.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API ARegular_Enemy : public ACharacter, public IEnemy, public IFighter,
                                          public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = AI)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnim;

	UPROPERTY(EditAnywhere, Category = "Hurt Animation")
	UAnimMontage* HurtAnimMontage;

	class AAIController* ControllerRef;

public:
	// Sets default values for this character's properties
	ARegular_Enemy();

	uint8 TeamID = 1;

	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Component")
	class UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDead{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPlayerDetected{false};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Location")
	FVector OriginalLocation;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Location")
	FRotator OriginalRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI)
	UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sense Config")
	float LoseSightDelay{5.f};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Location")
	bool bCanSeePlayer{false};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void HandlePlayerDeath();

	UFUNCTION(BlueprintCallable)
	void DetectPlayer(class AActor* ActorDetected, class APawn* OtherPawn);

	UFUNCTION(BlueprintCallable)
	void LosePlayer();

	UFUNCTION(BlueprintCallable, Category= "Enemy Death")
	void HandleDeath();

	UFUNCTION(BlueprintCallable)
	void PlayHurtAnimation();

	UFUNCTION(BlueprintCallable)
	void Knockback(AActor* Attacker);

	virtual float GetMeleeRange() override;

	virtual float GetDamage() override;

	virtual void Attack() override;

	virtual float GetAnimDuration() override;

	virtual bool IsDead_Implementation() const override;

	void HandleDisableCollisionOnDeath();

	void HandleSetPlayerVisibility();

	UFUNCTION()
	void FinishDeathAnim();
};
