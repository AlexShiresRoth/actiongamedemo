// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTTask_RegainPower.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "Interfaces/Fighter.h"
#include "Interfaces/RegenerateAbility.h"

//TODO I think this should run until enemy regains their health fully
// TODO need to check if they have returned to the 
EBTNodeResult::Type UBTTask_RegainPower::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	ACharacter* Character = AIController->GetCharacter();

	if (!Character)
	{
		return EBTNodeResult::Failed;
	}

	if (USkeletalMeshComponent* Mesh = Character->GetMesh())
	{
		if (UAnimInstance* AnimInstance = Mesh->GetAnimInstance())
		{
			if (AnimInstance->GetClass()->ImplementsInterface(URegenerateAbility::StaticClass()))
			{
				IRegenerateAbility::Execute_SetIsRegenerateAbilityState(AnimInstance, true);
			}
		}
	}

	// TODO set to regen state in animation based on interface
	// TODO create tick task to regen health only when regen state
	// TODO call the chartacter class to spawn the particle which I think will just be a function on an interface
	// which is then overriden based on that character
	// TODO then we can finish the task when health has regained or interrupted?

	return EBTNodeResult::InProgress;
}
