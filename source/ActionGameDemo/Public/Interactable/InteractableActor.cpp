// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/InteractableActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
// Sets default values
AInteractableActor::AInteractableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetWorld()->GetFirstPlayerController()->GetCharacter();
	PlayerRef = Cast<AActor>(CharacterRef);
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableActor::HandleInteraction()
{
	if (!bIsOverlapping)
	{
		UE_LOG(LogTemp, Warning, TEXT("InteractableActor::HandleInteraction not overlapping"));
		return;
	}

	if (PlayerRef != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Overlapped Actor %s"), *PlayerRef->GetName());
	}
}

void AInteractableActor::HandleOnBeginOverlapEvent(AActor* OverlappingActor)
{
	if (OverlappingActor == nullptr)
	{
		return;
	}

	// Only want to render the widget if the player runs into the collision sphere
	if (OverlappingActor == PlayerRef)
	{
		bIsOverlapping = true;
	}
}

void AInteractableActor::HandleOnEndOverlapEvent(AActor* OverlappingActor)
{
	if (OverlappingActor == nullptr)
	{
		return;
	}
	// Only end overlap if player is the one leaving the area
	if (OverlappingActor == PlayerRef)
	{
		bIsOverlapping = false;
	}
}

void AInteractableActor::HandleItemsOnActor()
{
	if (Items.Num() > 0)
	{
		for (const AItem* Item : Items)
		{
			UE_LOG(LogTemp, Warning, TEXT("Item %s"), *Item->GetName());
		}
	}
}
