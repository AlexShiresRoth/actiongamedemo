// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/CompanionReadyToFire.h"

#include "AIController.h"
#include "Animations/CompanionAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "combat/CombatComponent.h"
#include "combat/CombatManager.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


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
		if (const AActor* Enemy = Cast<AActor>(BlackboardComp->GetValueAsObject(FName("Enemy"))))
		{
			IIIsGettingReadyToFire::Execute_SetIsGettingReadyToFire(AnimInstance, true);
		}
	}

	return EBTNodeResult::Succeeded;
}
