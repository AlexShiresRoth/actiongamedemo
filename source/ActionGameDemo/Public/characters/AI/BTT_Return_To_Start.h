// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Return_To_Start.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTT_Return_To_Start : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_Return_To_Start();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
