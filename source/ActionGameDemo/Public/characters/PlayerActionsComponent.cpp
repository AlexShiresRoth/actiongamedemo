// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPlayerActionsComponent::UPlayerActionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();

	MovementComp = CharacterRef->GetCharacterMovement();

	if (!CharacterRef->Implements<UMainPlayer>())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player does not implement IMainPlayer"));
		return;
	}

	IPlayerRef = Cast<IMainPlayer>(CharacterRef);
}

// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerActionsComponent::Sprint()
{
	if (!IPlayerRef->HasEnoughStamina(SprintCost))
	{
		Walk();
		return;
	}

	if (MovementComp->Velocity.Equals(FVector::ZeroVector, 1))
	{
		return;
	}

	MovementComp->MaxWalkSpeed = SprintSpeed;

	OnSprintDelegate.Broadcast(SprintCost);
}

void UPlayerActionsComponent::Walk()
{
	MovementComp->MaxWalkSpeed = WalkSpeed;
}

void UPlayerActionsComponent::Roll()
{
	if (bIsRollActive || !IPlayerRef->HasEnoughStamina(RollCost))
	{
		return;
	}

	bIsRollActive = true;

	OnRollDelegate.Broadcast(RollCost);

	// handle the direction and rotation of where the player is rolling
	// for both from idle and moving
	const FVector Direction{
		CharacterRef->GetCharacterMovement()->Velocity.Length() < 1
			? CharacterRef->GetActorForwardVector()
			: CharacterRef->GetLastMovementInputVector()
	};

	const FRotator NewRotation{
		UKismetMathLibrary::MakeRotFromX(Direction)
	};


	CharacterRef->SetActorRotation(NewRotation);
	float Duration{CharacterRef->PlayAnimMontage(RollAnimMontage)};

	FTimerHandle RollTimerHandle;

	CharacterRef->GetWorldTimerManager().SetTimer(
		RollTimerHandle,
		this,
		&UPlayerActionsComponent::FinishRollAnim,
		Duration,
		false);
}

void UPlayerActionsComponent::FinishRollAnim()
{
	bIsRollActive = false;
}
