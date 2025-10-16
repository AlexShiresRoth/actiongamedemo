// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_BlockingMonitor.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTT_BlockingMonitor : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsBlocking = false;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
