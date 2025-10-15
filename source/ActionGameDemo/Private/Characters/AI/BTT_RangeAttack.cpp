// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTT_RangeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EEnemyState.h"
#include "Interfaces/Fighter.h"

EBTNodeResult::Type UBTT_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* CharacterRef{OwnerComp.GetAIOwner()->GetPawn<ACharacter>()};

	if (!IsValid(CharacterRef))
	{
		UE_LOG(LogTemp, Error, TEXT("Character is invalid"));
		return EBTNodeResult::Failed;
	}

	float Distance{
		// TODO should change this to an enum
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("Distance"))
	};


	IFighter* FighterRef{
		Cast<IFighter>(
			OwnerComp.GetAIOwner()->GetCharacter())
	};

	if (!FighterRef)
	{
		UE_LOG(LogTemp, Error, TEXT("Fighter is invalid"));
		return EBTNodeResult::Failed;
	}


	if (Distance < FighterRef->GetMeleeRange())
	{
		// TODO change CurrentState to Enum
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), Melee);

		AbortTask(OwnerComp, NodeMemory);

		return EBTNodeResult::Aborted;
	}

	CharacterRef->PlayAnimMontage(AnimMontage);

	double RandomValue{UKismetMathLibrary::RandomFloat()};

	if (RandomValue > Threshold)
	{
		Threshold = 0.9;
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), Charge);
	}
	else
	{
		Threshold -= 0.1;
	}

	return EBTNodeResult::Succeeded;
}
