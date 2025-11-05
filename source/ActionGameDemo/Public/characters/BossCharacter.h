// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Interfaces/Fighter.h"
#include "EEnemyState.h"
#include "GenericTeamAgentInterface.h"
#include "combat/CharacterAudioComponent.h"
#include "combat/CombatManager.h"
#include "Perception/AIPerceptionComponent.h"
#include "BossCharacter.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API ABossCharacter : public ACharacter, public IEnemy, public IFighter,
                                          public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnim;

	ACombatManager* CombatManager;

protected:
	class AAIController* ControllerRef;

public:
	// Sets default values for this character's properties
	ABossCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = BossName)
	FString BossName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Component")
	class UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI)
	UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI)
	UCharacterAudioComponent* CharacterAudioComp;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead{false};

	uint8 TeamID = 1;

	virtual FGenericTeamId GetGenericTeamId() const override { return FGenericTeamId(TeamID); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Boss Character")
	void DetectPlayer(class AActor* ActorDetected, class AActor* OtherActor);

	virtual float GetDamage() override;

	virtual void Attack() override;

	virtual float GetAnimDuration() override;

	virtual float GetMeleeRange() override;

	UFUNCTION()
	void HandlePlayerDeath();

	UFUNCTION(BlueprintCallable, Category = "Boss Character")
	void HandleDeath();

	UFUNCTION()
	void FinishDeathAnim();
};
