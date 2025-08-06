// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTT_MeleeAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "Interfaces/Fighter.h"
#include "GameFramework/Character.h"
#include "Characters/EEnemyState.h"
#include "Interfaces/Enemy.h"

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsFinished = false;

	float Distance{
		// TODO change this to an enum
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"))
	};

	AAIController* AIRef{OwnerComp.GetAIOwner()};

	if (Distance > AttackRadius)
	{
		APawn* PlayerRef{GetWorld()->GetFirstPlayerController()->GetPawn()};

		FAIMoveRequest MoveRequest{PlayerRef};
		MoveRequest.SetUsePathfinding(true);
		MoveRequest.SetAcceptanceRadius(AcceptableRadius);

		AIRef->ReceiveMoveCompleted.AddUnique(
			MoveDelegate);

		AIRef->MoveTo(MoveRequest);
		AIRef->SetFocus(PlayerRef);
	}
	else
	{
		IFighter* FighterRef{
			Cast<IFighter>(
				AIRef->GetCharacter())
		};

		UE_LOG(LogTemp, Error, TEXT("Attacking!!!!!!! %f"), Distance);
		FighterRef->Attack();

		FTimerHandle AttackTimerHandle;

		AIRef->GetCharacter()->GetWorldTimerManager().SetTimer(
			AttackTimerHandle,
			this,
			&UBTT_MeleeAttack::FinishAttackTask,
			FighterRef->GetAnimDuration(),
			false);
	}

	return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	float Distance{
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"))
	};

	AAIController* AIRef{OwnerComp.GetAIOwner()};

	IFighter* FighterRef{
		Cast<IFighter>(
			AIRef->GetCharacter())
	};

	if (!FighterRef) { return FinishLatentTask(OwnerComp, EBTNodeResult::Aborted); }

	if (Distance > FighterRef->GetMeleeRange())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(
			TEXT("CurrentState"),
			Range);

		AbortTask(OwnerComp, NodeMemory);

		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);

		AIRef->StopMovement();

		AIRef->ClearFocus(EAIFocusPriority::Gameplay);

		AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
	}


	if (!bIsFinished)
	{
		return;
	}


	OwnerComp.GetAIOwner()->ReceiveMoveCompleted.Remove(MoveDelegate);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
	bNotifyTick = true;

	// so each enemy has their own attack instance
	// will need to add this property to each task
	bCreateNodeInstance = true;

	MoveDelegate.BindUFunction(this, "FinishAttackTask");
}

void UBTT_MeleeAttack::FinishAttackTask()
{
	bIsFinished = true;
}
