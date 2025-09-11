// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI/AICompanionController.h"

#include "Perception/AIPerceptionComponent.h"

AAICompanionController::AAICompanionController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 3000.f;
	SightConfig->LoseSightRadius = 3500.f;
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	SightConfig->SetMaxAge(5.f);

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

ETeamAttitude::Type AAICompanionController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(&Other))
	{
		FGenericTeamId OtherTeam = TeamAgent->GetGenericTeamId();

		UE_LOG(LogTemp, Warning, TEXT("GetTeamAttitudeTowards %d"), OtherTeam.GetId());

		if (OtherTeam == FGenericTeamId(1)) // Enemies are team 1
		{
			return ETeamAttitude::Hostile;
		}
		if (OtherTeam == GetGenericTeamId()) // Same team as companion
		{
			return ETeamAttitude::Friendly;
		}
		return ETeamAttitude::Neutral;
	}
	return ETeamAttitude::Neutral;
}

void AAICompanionController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning,
	       TEXT("AAICompanionController::WHY DOES THIS NOT WORK!?!?!?!?!?!?!?!?"));
	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAICompanionController::OnPerceptionUpdated);
	}
}

void AAICompanionController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(LogTemp, Warning, TEXT("Companion sees: %s"), *Actor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Companion lost sight of: %s"), *Actor->GetName());
	}
}
