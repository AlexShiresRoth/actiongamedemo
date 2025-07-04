// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/OpenLevel.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Characters/PlayerActionsComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOpenLevel::AOpenLevel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOpenLevel::BeginPlay()
{
	Super::BeginPlay();


	CharacterRef = GetWorld()->GetFirstPlayerController()->GetCharacter();
	PlayerRef = Cast<AActor>(CharacterRef);

	if (UPlayerActionsComponent* PlayerActionsComponent = PlayerRef->FindComponentByClass<UPlayerActionsComponent>())
	{
		PlayerActionsComponent->OnInteractDelegate.AddDynamic(this, &AOpenLevel::HandleOpenLevel);
	}
}

// Called every frame
void AOpenLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TODO this currently works but not when levelToOpen is a UWorld object, why?
void AOpenLevel::HandleOpenLevel(AActor* InteractedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Opening Level s"));
	if (LevelToOpen.IsValid())
	{
		// FName LevelName = FName(*LevelToOpen.GetAssetName());
		UGameplayStatics::OpenLevel(this, LevelToOpen);
		UE_LOG(LogTemp, Warning, TEXT("Opened Level"));
	}
}

void AOpenLevel::HandleOnBeginOverlapEvent(AActor* OverlappingActor)
{
	if (OverlappingActor != nullptr)
	{
		bIsOverlapping = true;
	}
}

void AOpenLevel::HandleOnEndOverlapEvent(AActor* OverlappingActor)
{
	if (OverlappingActor != nullptr && bIsOverlapping)
	{
		bIsOverlapping = false;
	}
}
