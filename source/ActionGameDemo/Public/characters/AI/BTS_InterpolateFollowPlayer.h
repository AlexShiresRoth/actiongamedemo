// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "BTS_InterpolateFollowPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTS_InterpolateFollowPlayer : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_InterpolateFollowPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Blackboard key to write the smoothed follow location
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FName FollowLocationKey = "FollowLocation";

	UPROPERTY(EditAnywhere, Category="Blackboard")
	float FollowRadius{400.f};
	// Interpolation speed
	UPROPERTY(EditAnywhere, Category="Smoothing")
	float InterpSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category="Smoothing")
	float RotationInterpSpeed = 5.f;
};
