// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BossCharacter.h"
#include "Enums/FightStages.h"
#include "SwordBoss.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API ASwordBoss : public ABossCharacter
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	class UBlackboardComponent* BossBlackboardComponent;

public:
	ASwordBoss();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
	TEnumAsByte<EFightStages> FightStage;
};
