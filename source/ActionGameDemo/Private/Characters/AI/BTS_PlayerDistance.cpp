// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTS_PlayerDistance.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/Enemy.h"

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller) { return; }

	FVector EnemyLocation{OwnerComp.GetAIOwner()->GetPawn<ACharacter>()->GetActorLocation()};
	FVector PlayerLocation{GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()};

	float Distance{static_cast<float>(FVector::Distance(EnemyLocation, PlayerLocation))};

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(
		TEXT("Distance"),
		Distance);
}
