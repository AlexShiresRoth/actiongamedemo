// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_BlockingMonitor.h"

#include "AIController.h"
#include "Animations/EnemyAnimInstance.h"
#include "Characters/Regular_Enemy.h"
#include "Characters/Sword_Enemy.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type UBTT_BlockingMonitor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI{OwnerComp.GetAIOwner()};
	ACharacter* Char{AI->GetCharacter()};

	if (!Char)
	{
		return EBTNodeResult::Failed;
	}

	if (USkeletalMeshComponent* Mesh = Char->GetMesh())
	{
		if (!Mesh)
		{
			return EBTNodeResult::Failed;
		}

		if (UAnimInstance* Anim = Mesh->GetAnimInstance())
		{
			if (!Anim)
			{
				return EBTNodeResult::Failed;
			}

			if (UEnemyAnimInstance* EnemyAnim = Cast<UEnemyAnimInstance>(Anim))
			{
				EnemyAnim->SetIsBlocking(bIsBlocking);
			}
		}
	}

	return EBTNodeResult::InProgress;
}

void UBTT_BlockingMonitor::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
