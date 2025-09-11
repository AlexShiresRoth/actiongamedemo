// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_CompanionFindEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_CompanionFindEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

	if (!BB)
	{
		return EBTNodeResult::Failed;
	}

	AActor* ActorToFocus = Cast<AActor>(BB->GetValueAsObject(FName("Enemy")));

	if (!ActorToFocus)
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetAIOwner()->SetFocus(ActorToFocus);

	return EBTNodeResult::Succeeded;
}
