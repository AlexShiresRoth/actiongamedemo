// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/InteractableActor.h"

#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "UI/ItemsContainer.h"
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

	if (UPlayerActionsComponent* PlayerActionsComponent = PlayerRef->FindComponentByClass<UPlayerActionsComponent>())
	{
		PlayerActionsComponent->OnInteractDelegate.AddDynamic(this, &AInteractableActor::HandleInteractedWith);
	}
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

void AInteractableActor::HandleInteractedWith(AActor* InteractedActor)
{
	if (InteractedActor == this)
	{
		UItemsContainer* ItemsContainer = CreateWidget<UItemsContainer>(GetWorld(), ItemsWidgetClass);

		if (ItemsContainer != nullptr && !ItemsContainer->IsInViewport())
		{
			ItemsContainer->AddToViewport();

			ItemsContainer->SetItems(Items);
		}
	}
}
