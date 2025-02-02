// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lockon_Component.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API ULockon_Component : public UActorComponent
{
	GENERATED_BODY()

private:
	ACharacter *OwnerRef;

	APlayerController *PlayerControllerRef;

	class UCharacterMovementComponent *CharacterMovementRef;

	FRotator *RotationResult;

	class USpringArmComponent *SpringArmComponent;

public:
	// Sets default values for this component's properties
	ULockon_Component();

	AActor *CurrentTargetActor;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartLockon(float InRadius = 750.f);

	void StopLockon();

	UFUNCTION(BlueprintCallable, Category = "Lockon")
	void ToggleLockon(float Radius = 750.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lockon")
	double BreakDistance{1000.0};

public:
	// Called every frame
	virtual void
	TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
