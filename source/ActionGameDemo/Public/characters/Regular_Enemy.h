// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Interfaces/Fighter.h"
#include "Regular_Enemy.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API ARegular_Enemy : public ACharacter, public IEnemy, public IFighter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARegular_Enemy();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Component")
	class UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(class APawn *PawnDetected, class APawn* OtherPawn);
	
};

