// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SwordBoss.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASwordBoss::BeginPlay()
{
	Super::BeginPlay();

	if (BossBlackboardComponent)
	{
		BossBlackboardComponent->SetValueAsEnum("FightStages", FightStage);
	}
}

ASwordBoss::ASwordBoss()
{
	AAIController* AIControllerRef = GetController<AAIController>();

	if (AIControllerRef)
	{
		BossBlackboardComponent = AIControllerRef->GetBlackboardComponent();
	}
}
