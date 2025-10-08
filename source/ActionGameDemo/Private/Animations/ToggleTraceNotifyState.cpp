// Fill out your copyright notice in the Description page of Project Settings.

#include "Animations/ToggleTraceNotifyState.h"
#include "Combat/TraceComponent.h"

// This can be refactored if we want
void UToggleTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp,
                                          UAnimSequenceBase* Animation,
                                          float TotalDuration,
                                          const FAnimNotifyEventReference& EventReference)
{
	// Without these conditions, opening the animation in editor can cause a crash
	if (!MeshComp || !Animation)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();

	if (!Owner)
	{
		return;
	}

	UTraceComponent* TraceComp = Owner->FindComponentByClass<UTraceComponent>();

	if (!IsValid(TraceComp))
	{
		return;
	}

	TraceComp->bIsAttacking = true;
}

void UToggleTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp,
                                        UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !Animation)
	{
		return;
	}

	AActor* Owner = MeshComp->GetOwner();

	if (!Owner)
	{
		return;
	}

	UTraceComponent* TraceComp = Owner->FindComponentByClass<UTraceComponent>();

	if (!IsValid(TraceComp))
	{
		return;
	}

	TraceComp->bIsAttacking = false;
}
