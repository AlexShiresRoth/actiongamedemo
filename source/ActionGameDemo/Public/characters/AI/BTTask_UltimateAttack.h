// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Characters/EEnemyState.h"
#include "BTTask_UltimateAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTTask_UltimateAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAnimMontage* UltimateAttackMontage;

	UPROPERTY(EditAnywhere)
	bool bCanUseUltimate{false};

protected:
	UBTTask_UltimateAttack();

	virtual EBTNodeResult::Type
	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
