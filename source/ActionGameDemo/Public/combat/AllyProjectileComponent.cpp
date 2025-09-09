// Fill out your copyright notice in the Description page of Project Settings.


#include "combat/AllyProjectileComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values for this component's properties
UAllyProjectileComponent::UAllyProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAllyProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UAllyProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAllyProjectileComponent::SpawnProjectile(FName ComponentName, TSubclassOf<AActor> ProjectileClass)
{
	USceneComponent* SpawnPointComp{Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(ComponentName))};

	FVector SpawnLocation{SpawnPointComp->GetComponentLocation()};

	FVector PlayerLocation{GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()};

	FRotator SpawnRotation{FRotator::ZeroRotator};

	if (APawn* CompanionPawn = Cast<APawn>(GetOwner()))
	{
		if (AAIController* CompanionController = Cast<AAIController>(CompanionPawn->GetController()))
		{
			if (UBlackboardComponent* BB = CompanionController->GetBlackboardComponent())
			{
				const FVector EnemyLocation = BB->GetValueAsVector("EnemyLocation");
				if (!EnemyLocation.ContainsNaN())
				{
					SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, EnemyLocation);
				}
			}
		}
	}

	GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);
}
