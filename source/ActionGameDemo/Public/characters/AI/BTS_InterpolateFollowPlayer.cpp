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

	FVector CurrentFollow = BB->GetValueAsVector(FollowLocationKey);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector Offset = CurrentFollow - PlayerLocation;

	static bool bInitialized = false;
	if (!bInitialized || CurrentFollow.IsNearlyZero())
	{
		float Angle = FMath::FRandRange(0.f, 2 * PI);
		CurrentFollow = PlayerLocation + FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * FollowRadius;
		BB->SetValueAsVector(FollowLocationKey, CurrentFollow);
		bInitialized = true;
		return;
	}

	if (Offset.IsNearlyZero())
	{
		float Angle = FMath::FRandRange(0.f, 2 * PI);
		Offset = FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.f) * FollowRadius;
	}
	else
	{
		Offset = Offset.GetSafeNormal() * FollowRadius;
	}

	float RandomOffset = FMath::FRandRange(-50.f, 50.f);
	FVector TargetLocation = PlayerLocation + Offset + FVector(RandomOffset, RandomOffset, 0.f);

	// TODO - fix companion constantly rotating!
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
