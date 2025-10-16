// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTT_BlockingMonitor.h"

#include "AIController.h"
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

	if (ASword_Enemy* EnemyRef = Cast<ASword_Enemy>(Char))
	{
		EnemyRef->HandleBlocking();
	}

	return EBTNodeResult::InProgress;
}

void UBTT_BlockingMonitor::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
