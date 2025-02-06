// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "Interfaces/Fighter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API APlayerCharacter : public ACharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadonly, Category = "Player Character")
	class UPlayerAnimInstance_USE *PlayerAnimInstance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual float GetDamage() override;
};
