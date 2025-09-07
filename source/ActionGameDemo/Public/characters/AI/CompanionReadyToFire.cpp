// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CompanionReadyToFire.h"

#include "AIController.h"
#include "Animations/CompanionAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "combat/CombatComponent.h"
#include "combat/CombatManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// TODO BT needs to be fixed up
// TODO need to reset after firing, also need to handle firing
// TODO enemy location needs to be reset after no valid enemies visible - maybe we can do that in the combat manager
// TODO need another task to actually fire, do we need companion combat state enum and keys?
// TODO need a companion projectile
// TODO companion moiving to enemy doesn't really show walking normally

EBTNodeResult::Type UCompanionReadyToFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	USkeletalMeshComponent* MeshComp = OwnerComp.GetAIOwner()->GetCharacter()->GetMesh();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (MeshComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Skeeltal mesh comp on companion"));
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();

	if (AnimInstance->GetClass()->ImplementsInterface(UIIsGettingReadyToFire::StaticClass()))
	{
		FVector EnemyLocation = BlackboardComp->GetValueAsVector("EnemyLocation");

		if (!EnemyLocation.ContainsNaN())
		{
			IIIsGettingReadyToFire::Execute_SetIsGettingReadyToFire(AnimInstance, true);
		}
	}

	return EBTNodeResult::Succeeded;
}
