// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask_BossMeleeState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "Animations/EnemyAnimInstance.h"
#include "Interfaces/Fighter.h"
#include "GameFramework/Character.h"
#include "Characters/EEnemyState.h"
#include "Characters/LookAtPlayerComponent.h"
#include "Interfaces/IChargeAttack.h"
#include "Interfaces/RangeAttack.h"
#include "Interfaces/UltimateAttack.h"

UBTTask_BossMeleeState::UBTTask_BossMeleeState()
{
	bNotifyTick = true;

	// so each enemy has their own attack instance
	// will need to add this property to each task
	bCreateNodeInstance = true;

	MoveDelegate.BindUFunction(this, "FinishAttackTask");
}

void UBTTask_BossMeleeState::AbortMeleeAttack(AAIController* AIRef, UBehaviorTreeComponent& OwnerComp,
                                              uint8* NodeMemory)
{
	AbortTask(OwnerComp, NodeMemory);

	FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);

	AIRef->StopMovement();

	AIRef->ClearFocus(EAIFocusPriority::Gameplay);

	AIRef->ReceiveMoveCompleted.Remove(MoveDelegate);
}

void UBTTask_BossMeleeState::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	float Distance{
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"))
	};

	AAIController* AIRef{OwnerComp.GetAIOwner()};
	APawn* EnemyPawn{AIRef->GetPawn()};
	ACharacter* PlayerRef = GetWorld()->GetFirstPlayerController()->GetCharacter();
	IFighter* FighterRef{
		Cast<IFighter>(
			AIRef->GetCharacter())
	};

	if (!FighterRef) { return FinishLatentTask(OwnerComp, EBTNodeResult::Aborted); }

	// if (Distance > FighterRef->GetMeleeRange())
	// {
	// 	if (EnemyPawn->GetClass()->ImplementsInterface(URangeAttack::StaticClass()))
	// 	{
	// 		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(
	// 			TEXT("CurrentState"),
	// 			Range);
	// 		AbortMeleeAttack(AIRef, OwnerComp, NodeMemory);
	// 	}
	//
	// 	if (EnemyPawn->GetClass()->ImplementsInterface(UIChargeAttack::StaticClass()))
	// 	{
	// 		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(
	// 			TEXT("CurrentState"),
	// 			Charge);
	//
	// 		AbortMeleeAttack(AIRef, OwnerComp, NodeMemory);
	// 	}
	// }

	if (!bIsFinished)
	{
		return;
	}

	OwnerComp.GetAIOwner()->ReceiveMoveCompleted.Remove(MoveDelegate);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}


void UBTTask_BossMeleeState::FinishAttackTask()
{
	if (LookAtPlayerComponent)
	{
		LookAtPlayerComponent->bCanRotate = false;
	}

	bIsFinished = true;
}

EBTNodeResult::Type UBTTask_BossMeleeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	bIsFinished = false;

	float Distance{
		// TODO change this to an enum
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"))
	};

	AAIController* AIRef{OwnerComp.GetAIOwner()};
	APawn* EnemyPawn{AIRef->GetPawn()};
	APawn* PlayerRef{GetWorld()->GetFirstPlayerController()->GetPawn()};


	IFighter* FighterRef{
		Cast<IFighter>(
			AIRef->GetCharacter())
	};

	// TODO change this to boss anim instance
	// if (USkeletalMeshComponent* Mesh = AIRef->GetCharacter()->GetMesh())
	// {
	// 	if (Mesh)
	// 	{
	// 		if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
	// 		{
	// 			if (UEnemyAnimInstance* EnemyAnim = Cast<UEnemyAnimInstance>(AnimInstance))
	// 			{
	// 				if (EnemyAnim->bIsBlocking)
	// 				{
	// 					// End blocking
	// 					EnemyAnim->SetIsBlocking(false);
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	if (Distance > AttackRadius)
	{
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
		BossCharacter = OwnerComp.GetAIOwner()->GetCharacter();

		LookAtPlayerComponent = BossCharacter->FindComponentByClass<ULookAtPlayerComponent>();

		if (!BossCharacter || !LookAtPlayerComponent) { return EBTNodeResult::Failed; }

		LookAtPlayerComponent->bCanRotate = true;
		// TODO maybe I can add a combo attack so it's not just one sword swing
		FighterRef->Attack();
		UE_LOG(LogTemp, Warning, TEXT("boss attacking!!!"))
		FTimerHandle AttackTimerHandle;

		AIRef->GetCharacter()->GetWorldTimerManager().SetTimer(
			AttackTimerHandle,
			this,
			&UBTTask_BossMeleeState::FinishAttackTask,
			FighterRef->GetAnimDuration(),
			false);
	}

	return EBTNodeResult::InProgress;
}
