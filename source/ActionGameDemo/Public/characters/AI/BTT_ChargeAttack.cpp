// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTT_ChargeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/EEnemyState.h"

UBTT_ChargeAttack::UBTT_ChargeAttack()
{
	bNotifyTick = true;

	MoveCompletedDelegate.BindUFunction(
		this,
		"HandleMoveCompleted");
}

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ControllerRef = OwnerComp.GetAIOwner();
	CharacterRef = ControllerRef->GetCharacter();

	// anim instance lives on the mesh
	BossAnim = Cast<UBossAnimInstance>(CharacterRef->GetMesh()->GetAnimInstance());

	if (!BossAnim) { return EBTNodeResult::Failed; }
	BossAnim->bIsCharging = true;

	// TODO we should change IsReadyToChage to an enum
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(
		TEXT("IsReadyToCharge"),
		false // this text value should be a key in the blackboard BB_Boss and is case sensitive
	);

	bIsFinished = false;
	// also this key is used in the ABP_Boss in editor for anim notify event

	return EBTNodeResult::InProgress;
}

void UBTT_ChargeAttack::ChargeAtPlayer()
{
	APawn* PlayerRef{GetWorld()->GetFirstPlayerController()->GetPawn()};

	FVector PlayerLocation{PlayerRef->GetActorLocation()};

	FAIMoveRequest MoveRequest{PlayerLocation};

	MoveRequest.SetUsePathfinding(true);

	MoveRequest.SetAcceptanceRadius(AcceptableRadius);

	ControllerRef->MoveTo(MoveRequest);
	ControllerRef->SetFocus(PlayerRef);
	ControllerRef->ReceiveMoveCompleted.AddUnique(
		MoveCompletedDelegate);

	// Set charge speed
	OriginalWalkSpeed = CharacterRef->GetCharacterMovement()->MaxWalkSpeed;
	CharacterRef->GetCharacterMovement()->MaxWalkSpeed = ChargeWalkSpeed;
}

void UBTT_ChargeAttack::HandleMoveCompleted()
{
	BossAnim->bIsCharging = false;

	FTimerHandle AttackTimerHandle;

	CharacterRef->GetWorldTimerManager().SetTimer(
		AttackTimerHandle,
		this,
		&UBTT_ChargeAttack::FinishAttackTask, 1.0f, false);

	// Reset charge speed
	CharacterRef->GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
}

void UBTT_ChargeAttack::FinishAttackTask()
{
	bIsFinished = true;
}

void UBTT_ChargeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool bIsReadyToCharge{
		OwnerComp.GetBlackboardComponent()->GetValueAsBool(
			TEXT("IsReadyToCharge") // this text value should be a key in the blackboard BB_Boss and is case sensitive
		)
	};

	if (bIsReadyToCharge)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsReadyToCharge"), false);

		ChargeAtPlayer();
	}

	if (!bIsFinished)
	{
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("CurrentState"), Melee);

	ControllerRef->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
