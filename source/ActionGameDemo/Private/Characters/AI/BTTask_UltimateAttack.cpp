// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask_UltimateAttack.h"
#include "AIController.h"
#include "Animations/EnemyAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "GameFramework/Character.h"
#include "Interfaces/UltimateAttack.h"

UBTTask_UltimateAttack::UBTTask_UltimateAttack()
{
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

// TODO - boss ultimate gets canceled if player is too close
// TODO I think boss should be invulnerable during ultimate
EBTNodeResult::Type UBTTask_UltimateAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController{OwnerComp.GetAIOwner()};
	ACharacter* CharacterRef{OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};

	if (!CharacterRef)
	{
		return EBTNodeResult::Failed;
	}

	if (!CharacterRef->GetClass()->ImplementsInterface(UUltimateAttack::StaticClass()))
	{
		return EBTNodeResult::Aborted;
	}

	USkeletalMeshComponent* Mesh = CharacterRef->GetMesh();

	if (!Mesh)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	if (!AnimInstance->GetClass()->ImplementsInterface(UUltimateAttack::StaticClass()))
	{
		return EBTNodeResult::Aborted;
	}

	IUltimateAttack::Execute_SetIsUltimateState(AnimInstance, false);
	IUltimateAttack::Execute_SetIsUltimateFinished(AnimInstance, false);

	EEnemyState CurrentState = static_cast<EEnemyState>(OwnerComp.GetBlackboardComponent()->GetValueAsEnum(
		TEXT("CurrentState")));

	if (CurrentState != Ultimate)
	{
		UE_LOG(LogTemp, Error, TEXT("ULTIMATE_ATTACK::Not in ultimate state!!!!"))
		return EBTNodeResult::Aborted;
	}

	bCanUseUltimate = OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanUseUltimate");

	if (!bCanUseUltimate)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", Melee);
		return EBTNodeResult::Aborted;
	}

	if (bCanUseUltimate)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Can use ultimate attack & implements interface"),
		       *CharacterRef->GetName());
		IUltimateAttack::Execute_SetIsUltimateState(AnimInstance, true);
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_UltimateAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController{OwnerComp.GetAIOwner()};
	ACharacter* CharacterRef{OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};

	if (!CharacterRef)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!CharacterRef->GetClass()->ImplementsInterface(UUltimateAttack::StaticClass()))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	USkeletalMeshComponent* Mesh = CharacterRef->GetMesh();

	if (!Mesh)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (!AnimInstance->GetClass()->ImplementsInterface(UUltimateAttack::StaticClass()))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	bool bIsFinished = IUltimateAttack::Execute_GetIsUltimateFinished(AnimInstance);

	if (bIsFinished)
	{
		UE_LOG(LogTemp, Error, TEXT("ULTIMATEATTACKTASK::FINISHING TASK"))
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", Idle);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
