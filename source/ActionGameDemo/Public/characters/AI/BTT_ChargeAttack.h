// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChargeAttack.generated.h"
/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTT_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	AAIController *ControllerRef;

	ACharacter *CharacterRef;

	class UBossAnimInstance *BossAnim;

	FScriptDelegate MoveCompletedDelegate;

	float OriginalWalkSpeed;

	UPROPERTY(EditAnywhere)
	float ChargeWalkSpeed{2000.0f};

	UPROPERTY(EditAnywhere)
	float AcceptableRadius{100.0f};

protected:
	virtual void TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

public:
	UBTT_ChargeAttack();

	virtual EBTNodeResult::Type
	ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

	void ChargeAtPlayer();

	UFUNCTION()
	void HandleMoveCompleted();

	UFUNCTION()
	void FinishAttackTask();
};
