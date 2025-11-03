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

public:
	ASwordBoss();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBlockComponent* BlockComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
	TEnumAsByte<EFightStages> FightStage;

	// TODO - can we set this to array and play hurt anim based on where it's hit?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boss)
	UAnimMontage* HurtMontage;

	UFUNCTION(BlueprintCallable, Category = Boss)
	void PlayHurtAnimation();
};
