// Fill out your copyright notice in the Description page of Project Settings.


#include "combat/BlockComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
// Sets default values for this component's properties
UBlockComponent::UBlockComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBlockComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBlockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBlockComponent::Check(AActor* Opponent)
{
	ACharacter *CharacterRef{GetOwner<ACharacter>()};

	// true means we can't block damage
	if (!CharacterRef->Implements<UMainPlayer>())
	{
		return true;
	}

	IMainPlayer *PlayerRef{Cast<IMainPlayer>(CharacterRef)};

	FVector OpponentForward{Opponent->GetActorForwardVector() };

	FVector PlayerForward{CharacterRef->GetActorForwardVector() };

	double Result{ FVector::DotProduct(OpponentForward, PlayerForward)};

	// if result is greater than 0 that means they are not looking at each other
	if (Result > 0 || !PlayerRef->HasEnoughStamina(StaminaCost))
	{
		return true;
	}

	CharacterRef->PlayAnimMontage(BlockAnimMontage);

	OnBlockDelegate.Broadcast(StaminaCost);
	
	// false will mean we can
	return false;
}

