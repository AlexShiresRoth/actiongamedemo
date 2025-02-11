// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTS_PlayerDistance.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    FVector EnemyLocation{OwnerComp.GetAIOwner()->GetPawn<ACharacter>()->GetActorLocation()};
    FVector PlayerLocation{GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()};

    float Distance{static_cast<float>(FVector::Distance(EnemyLocation, PlayerLocation))};

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(
        TEXT("Distance"),
        Distance);
}
