// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAudioComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API UCharacterAudioComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* CharacterRef;

public:
	// Sets default values for this component's properties
	UCharacterAudioComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	TArray<class USoundBase*> AttackAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	TArray<class USoundBase*> DamageAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	TArray<class USoundBase*> BlockAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	TArray<class USoundBase*> DeathAudio;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PlayAttackAudio();

	UFUNCTION(BlueprintCallable)
	void PlayDamageAudio();

	UFUNCTION(BlueprintCallable)
	void PlayBlockAudio();

	UFUNCTION(BlueprintCallable)
	void PlayDeathAudio();

	void PlayAudioAtLocation(USoundBase* Sound);
};
