// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CompanionCharacter.h"

#include "StatsComponent.h"
#include "combat/CombatComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "PlayerCharacter.h"
#include "Animations/CompanionAnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "combat/CombatManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACompanionCharacter::ACompanionCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

	// AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
}

// Called when the game starts or when spawned
void ACompanionCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIControllerRef = GetController<AAIController>();

	BlackboardComp = AIControllerRef->GetBlackboardComponent();

	ACharacter* PlayerRef = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));

	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("BlackboardComponent is null"));
		return;
	}

	if (PlayerRef)
	{
		BlackboardComp->SetValueAsObject("Player", PlayerRef);
		UE_LOG(LogTemp, Display, TEXT("Player value is %s"), *PlayerRef->GetName());
	}

	BlackboardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState);
}

// Called every frame
void ACompanionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	USkeletalMeshComponent* CompanionMesh = GetMesh();
	if (!CompanionMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("CompanionMesh is null"));
		return;
	}
	UCompanionAnimInstance* CompanionAnimInstance = Cast<UCompanionAnimInstance>(CompanionMesh->GetAnimInstance());

	if (CombatManager)
	{
		if (CombatManager->bIsInCombat)
		{
			if (CompanionAnimInstance)
			{
				BlackboardComp->SetValueAsEnum("CurrentState", Companion_Combat);
				// Need to change state machines here
				CompanionAnimInstance->bIsInCombat = true;

				// TODO Remove this - I need to create an EQS service to run to find enemy to attack
				// TODO also need to fix enemy, they seem to be still in charge mode even if losing sight of player
				CompanionAnimInstance->SetIsGettingReadyToFire_Implementation(true);
			}
		}
		else
		{
			if (CompanionAnimInstance)
			{
				BlackboardComp->SetValueAsEnum("CurrentState", Companion_Following);
				CompanionAnimInstance->bIsInCombat = false;
			}
		}
	}
}

// Called to bind functionality to input
void ACompanionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
