// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/BTS_InterpolateFollowPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryManager.h"

UBTS_InterpolateFollowPlayer::UBTS_InterpolateFollowPlayer()
{
	NodeName = "EQS Follow Player";
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
}

void UBTS_InterpolateFollowPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto* BB = OwnerComp.GetBlackboardComponent();
	auto* AIController = OwnerComp.GetAIOwner();
	if (!BB || !AIController)
	{
		return;
	}

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return;
	}

	APawn* CompanionPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!CompanionPawn)
	{
		return;
	}

	int Side = 1;

	FVector CurrentFollow = BB->GetValueAsVector(FollowLocationKey);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector PlayerForward = PlayerPawn->GetActorForwardVector();
	FVector PlayerRight = PlayerPawn->GetActorRightVector();
	FVector Offset = PlayerRight * (Side * FollowRadius);

	static bool bInitialized = false;
	if (!bInitialized || !BB->IsVectorValueSet(FollowLocationKey))
	{
		float Angle = FMath::FRandRange(0.f, 2 * PI);
		CurrentFollow = PlayerLocation + FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * FollowRadius;
		BB->SetValueAsVector(FollowLocationKey, CurrentFollow);
		bInitialized = true;
		return;
	}

	FVector TargetLocation = PlayerLocation + Offset;
	if (!CurrentFollow.Equals(TargetLocation, 1.0f)) // 1 unit tolerance
	{
		FRotator CurrentRotation = CompanionPawn->GetActorRotation();
		FRotator DesiredRotation = (TargetLocation - CompanionPawn->GetActorLocation()).Rotation();
		FRotator SmoothedRotation = FMath::RInterpTo(CurrentRotation, DesiredRotation, DeltaSeconds,
		                                             RotationInterpSpeed);
		CompanionPawn->SetActorRotation(SmoothedRotation);

		FVector Smoothed = FMath::VInterpTo(CurrentFollow, TargetLocation, DeltaSeconds, InterpSpeed);
		BB->SetValueAsVector(FollowLocationKey, Smoothed);
	}
}
