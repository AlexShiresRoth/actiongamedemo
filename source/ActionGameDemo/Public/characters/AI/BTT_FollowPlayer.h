// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FollowPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UBTT_FollowPlayer : public UBTTaskNode
{
	GENERATED_BODY()

	AAIController* AIController;

	FScriptDelegate MoveCompleteDelegate;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AcceptableRadius{400.f};
};
