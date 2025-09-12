// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_CompanionFindEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTT_CompanionFindEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type
	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
