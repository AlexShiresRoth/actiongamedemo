// Fill out your copyright notice in the Description page of Project Settings.

#include "combat/Lockon_Component.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values for this component's properties
ULockon_Component::ULockon_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void ULockon_Component::BeginPlay()
{
	Super::BeginPlay();

	OwnerRef = GetOwner<ACharacter>();

	UE_LOG(LogTemp, Warning, TEXT("Owner Ref %s"), *OwnerRef->GetName());

	PlayerControllerRef = GetWorld()->GetFirstPlayerController();

	CharacterMovementRef = OwnerRef->GetCharacterMovement();

	SpringArmComponent = OwnerRef->FindComponentByClass<USpringArmComponent>();
}

void ULockon_Component::StartLockon(float InRadius)
{
	FHitResult OutResult;

	FVector CurrentLocation{OwnerRef->GetActorLocation()};

	FCollisionShape Sphere{FCollisionShape::MakeSphere(InRadius)};

	FCollisionQueryParams IgnoreParams{
		FName{TEXT("Ignore Collision Params")},
		false,
		OwnerRef,
	};

	bool bHasFoundTarget{
		GetWorld()->SweepSingleByChannel(
			OutResult,
			CurrentLocation,
			CurrentLocation,
			FQuat::Identity,
			// @note we can find the name of customn channels in the default engine.ini file ie search "Fighter"
			ECollisionChannel::ECC_GameTraceChannel1,
			Sphere,
			IgnoreParams),
	};

	if (!bHasFoundTarget)
	{
		return;
	}

	CurrentTargetActor = OutResult.GetActor();

	PlayerControllerRef->SetIgnoreLookInput(true);
	CharacterMovementRef->bOrientRotationToMovement = false;
	CharacterMovementRef->bUseControllerDesiredRotation = true;

	SpringArmComponent->TargetOffset = FVector{0.f, 0.f, 100.0f};
}

void ULockon_Component::StopLockon()
{

	CurrentTargetActor = nullptr;

	CharacterMovementRef->bOrientRotationToMovement = true;
	CharacterMovementRef->bUseControllerDesiredRotation = false;
	SpringArmComponent->TargetOffset = FVector::ZeroVector;

	PlayerControllerRef->ResetIgnoreLookInput();
}

void ULockon_Component::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		StopLockon();
	}
	else
	{
		StartLockon(Radius);
	}
}

// Called every frame
void ULockon_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor))
	{
		return;
	}

	FVector CurrentLocation{OwnerRef->GetActorLocation()};
	FVector TargetLocation{CurrentTargetActor->GetActorLocation()};

	double TargetDistance{FVector::Distance(CurrentLocation, TargetLocation)};

	if (TargetDistance > BreakDistance)
	{
		StopLockon();
		return;
	}

	TargetLocation.Z -= 125;

	FRotator NewRotation{UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation)};

	PlayerControllerRef->SetControlRotation(NewRotation);
}
