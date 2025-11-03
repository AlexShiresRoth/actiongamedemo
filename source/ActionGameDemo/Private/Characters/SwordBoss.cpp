// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SwordBoss.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// TODO - need a parent anim instance,to share setisblocking
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

	BlockComponent = CreateDefaultSubobject<UBlockComponent>(TEXT("BlockComponent"));
}

void ASwordBoss::PlayHurtAnimation()
{
	if (!HurtMontage || bIsDead) { return; }

	float AnimDuration{PlayAnimMontage(HurtMontage)};
}
