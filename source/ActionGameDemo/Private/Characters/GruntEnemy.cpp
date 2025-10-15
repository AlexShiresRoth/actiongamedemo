// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GruntEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void AGruntEnemy::DetectPlayer(class AActor* ActorDetected, class APawn* OtherPawn)
{
	const APawn* DetectedPawn = Cast<APawn>(ActorDetected);
	const AActor* MainPlayer = GetWorld()->GetFirstPlayerController()->GetCharacter();
	// detect only player
	if (DetectedPawn != OtherPawn)
	{
		return;
	}
	if (bIsDead || DetectedPawn != MainPlayer) { return; }

	if (BlackboardComp)
	{
		EEnemyState CurrentState{
			static_cast<EEnemyState>(BlackboardComp->GetValueAsEnum(TEXT("CurrentState")))
		};

		// TODO idk if we need this variable still
		bCanSeePlayer = true;

		if (CombatManager)
		{
			CombatManager->AddCombatTarget(ControllerRef->GetCharacter());
		}

		BlackboardComp->SetValueAsBool(TEXT("IsPlayerVisible"), true);

		BlackboardComp->SetValueAsEnum(TEXT("CurrentState"), Range);
	}
}
