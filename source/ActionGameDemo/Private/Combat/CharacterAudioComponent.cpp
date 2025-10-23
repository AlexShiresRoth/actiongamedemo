// Fill out your copyright notice in the Description page of Project Settings.


#include "combat/CharacterAudioComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharacterAudioComponent::UCharacterAudioComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterAudioComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCharacterAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterAudioComponent::PlayAttackAudio()
{
	if (AttackAudio.Num() > 0)
	{
		int RandomIndex{
			FMath::RandRange(0, AttackAudio.Num() - 1)
		};

		PlayAudioAtLocation(AttackAudio[RandomIndex]);
	}
}

void UCharacterAudioComponent::PlayDamageAudio()
{
	if (DamageAudio.Num() > 0)
	{
		int RandomIndex{
			FMath::RandRange(0, DamageAudio.Num() - 1)
		};

		PlayAudioAtLocation(DamageAudio[RandomIndex]);
	}
}

void UCharacterAudioComponent::PlayBlockAudio()
{
	if (BlockAudio.Num() > 0)
	{
		int RandomIndex{
			FMath::RandRange(0, BlockAudio.Num() - 1)
		};

		PlayAudioAtLocation(BlockAudio[RandomIndex]);
	}
}

void UCharacterAudioComponent::PlayDeathAudio()
{
	if (DeathAudio.Num() > 0)
	{
		int RandomIndex{
			FMath::RandRange(0, DeathAudio.Num() - 1)
		};

		PlayAudioAtLocation(DeathAudio[RandomIndex]);
	}
}

void UCharacterAudioComponent::PlayAudioAtLocation(USoundBase* Sound)
{
	FVector ActorLoc = GetOwner()->GetActorLocation();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, ActorLoc);
}
