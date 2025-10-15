// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Regular_Enemy.h"
#include "Interfaces/IChargeAttack.h"
#include "Interfaces/RangeAttack.h"
#include "GruntEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API AGruntEnemy : public ARegular_Enemy, public IRangeAttack, public IIChargeAttack
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DetectPlayer(class AActor* ActorDetected, class APawn* OtherPawn);
};
