// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask_UltimateAttack.h"
#include "AIController.h"
#include "Animations/EnemyAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "GameFramework/Character.h"
#include "Interfaces/UltimateAttack.h"

void UBTTask_UltimateAttack::ChangeState()
{
}

// TODO - this is a bit buggy at the moment	seems like while charging it breaks?
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

	bool bCanUseUltimate = OwnerComp.GetBlackboardComponent()->GetValueAsBool("CanUseUltimate");

	if (!bCanUseUltimate)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", Melee);
		return EBTNodeResult::Aborted;
	}

	float AnimDuration{0.f};

	if (bCanUseUltimate)
	{
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

		if (auto* EnemyAnimInstance = Cast<UEnemyAnimInstance>(AnimInstance))
		{
			EnemyAnimInstance->SetIsUltimateState(true);
		}
	}

	return EBTNodeResult::Succeeded;
}
