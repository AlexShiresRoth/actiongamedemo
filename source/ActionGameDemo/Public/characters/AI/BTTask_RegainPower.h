// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RegainPower.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTTask_RegainPower : public UBTTaskNode
{
	GENERATED_BODY()


	protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
