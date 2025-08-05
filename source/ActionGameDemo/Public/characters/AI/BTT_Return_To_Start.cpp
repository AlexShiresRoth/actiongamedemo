// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Return_To_Start.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_Return_To_Start::UBTT_Return_To_Start()
{
	NodeName = "Return_To_Start";
}

EBTNodeResult::Type UBTT_Return_To_Start::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("Return_To_Start::ExecuteTask"));

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FVector StartLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("StartLocation");

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(StartLocation);
	MoveRequest.SetAcceptanceRadius(50.f);

	FNavPathSharedPtr NavPath;
	AIController->MoveTo(MoveRequest, &NavPath);

	return EBTNodeResult::Succeeded;
}
