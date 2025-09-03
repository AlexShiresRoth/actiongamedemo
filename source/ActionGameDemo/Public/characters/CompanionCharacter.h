// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ECompanionState.h"
#include "GameFramework/Character.h"
#include "Interfaces/Fighter.h"
#include "Perception/AIPerceptionComponent.h"
#include "CompanionCharacter.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API ACompanionCharacter : public ACharacter, public IFighter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACompanionCharacter();

	virtual FGenericTeamId GetGenericTeamId() const override
	{
		return FGenericTeamId(0);
	}

	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	TEnumAsByte<ECompanionState> InitialState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Companion)
	bool bIsInParty{false};

	AAIController* AIControllerRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Component")
	class UStatsComponent* StatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI)
	UAIPerceptionComponent* AIPerceptionComp;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void DetectEnemy(class AActor* ActorDetected, class APawn* OtherPawn);
};
