// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Return_To_Start.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "Interfaces/Fighter.h"
#include "Navigation/PathFollowingComponent.h"

UBTT_Return_To_Start::UBTT_Return_To_Start()
{
	NodeName = "Return_To_Start";
}

// TODO need to set rotation to where the actor is headed 
EBTNodeResult::Type UBTT_Return_To_Start::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
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
	FRotator StartRotation = OwnerComp.GetBlackboardComponent()->GetValueAsRotator("StartRotation");

	float AcceptableDistance = 200.0f;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(StartLocation);
	MoveRequest.SetAcceptanceRadius(AcceptableDistance);


	FNavPathSharedPtr NavPath;
	AIController->MoveTo(MoveRequest, &NavPath);

	if (FVector::Dist(AIPawn->GetActorLocation(), StartLocation) <= AcceptableDistance)
	{
		AIPawn->SetActorRotation(StartRotation);
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), Idle);

	return EBTNodeResult::Succeeded;
}

void UBTT_Return_To_Start::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIRef{OwnerComp.GetAIOwner()};

	bool bIsPlayerVisible{OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsPlayerVisible"))};

	if (bIsPlayerVisible) { return FinishLatentTask(OwnerComp, EBTNodeResult::Aborted); }

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
