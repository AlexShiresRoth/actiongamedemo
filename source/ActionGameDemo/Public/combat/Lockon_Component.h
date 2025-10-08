// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lockon_Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockon_Component, OnUpdatedTargetDelegate, AActor *, NewTargetActorRef);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API ULockon_Component : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* OwnerRef;

	APlayerController* PlayerControllerRef;

	class UCharacterMovementComponent* CharacterMovementRef;

	FRotator* RotationResult;

	class USpringArmComponent* SpringArmComponent;

public:
	// Sets default values for this component's properties
	ULockon_Component();

	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintAssignable, Category = "Lockon")
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void StartLockon(float InRadius = 750.f);

	UFUNCTION(BlueprintCallable, Category = "Lockon")
	void ToggleLockon(float Radius = 750.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lockon")
	double BreakDistance{1000.0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lockon")
	FVector LockonLocation{0.f, 100.f, 50.f};

public:
	void StopLockon();
	// Called every frame
	virtual void
	TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
