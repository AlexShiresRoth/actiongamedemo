// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttack.generated.h"

/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float AttackRadius{200.0f};

	// The acceptable radius should always be less than the attack radius or bugs will happen
	UPROPERTY(EditAnywhere)
	float AcceptableRadius{100.0f};

	UPROPERTY(EditAnywhere)
	float MeleeSpeed{1000.f};

	UPROPERTY(EditAnywhere)
	float MeleeOrbitDistance{20.f};

	bool bIsFinished{false};

	FScriptDelegate MoveDelegate;

	void AbortMeleeAttack(AAIController* AIRef, UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UBTT_MeleeAttack();

	UFUNCTION()
	void FinishAttackTask();
};
