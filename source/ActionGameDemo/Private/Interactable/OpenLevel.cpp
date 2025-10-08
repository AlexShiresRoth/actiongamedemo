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

void AOpenLevel::HandleOpenLevel(AActor* InteractedActor)
{
	if (!LevelToLoad.IsNull())
	{
		UGameplayStatics::OpenLevel(this, FName(LevelToLoad.GetAssetName()));
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
