// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "EEnemyState.h"
#include "BossCharacter.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API ABossCharacter : public ACharacter, public IEnemy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	class UBlackboardComponent *BlackboardComp;

public:
	// Sets default values for this character's properties
	ABossCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Component")
	class UStatsComponent *StatsComp;

	UFUNCTION(BlueprintCallable, Category = "Boss Character")
	void DetectPawn(class APawn *PawnDetected, class APawn *OtherPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
