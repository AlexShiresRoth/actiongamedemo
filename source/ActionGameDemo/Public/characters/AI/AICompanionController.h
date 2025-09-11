// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AICompanionController.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API AAICompanionController : public AAIController
{
	GENERATED_BODY()

public:
	AAICompanionController();

	virtual FGenericTeamId GetGenericTeamId() const override
	{
		return FGenericTeamId(0);
	}

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=AI)
	UAIPerceptionComponent* PerceptionComp;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
