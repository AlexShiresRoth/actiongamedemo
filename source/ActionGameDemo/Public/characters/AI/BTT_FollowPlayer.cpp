// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_FollowPlayer.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

// TODO how do we handle the companion in the party and having them follow the player?
// TODO add execute task function
void UBTT_FollowPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerRef{GetWorld()->GetFirstPlayerController()->GetPawn()};

	FVector PlayerLocation{PlayerRef->GetActorLocation()};

	FAIMoveRequest MoveRequest{PlayerLocation};

	MoveRequest.SetUsePathfinding(true);

	MoveRequest.SetAcceptanceRadius(AcceptableRadius);

	AIController->MoveTo(MoveRequest);
	AIController->SetFocus(PlayerRef);
	AIController->ReceiveMoveCompleted.AddUnique(
		MoveCompleteDelegate);
}


