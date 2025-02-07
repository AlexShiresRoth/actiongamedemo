// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	USkeletalMeshComponent *SkeletalComp;

	UPROPERTY(EditAnywhere, Category = "Trace")
	FName Start;

	UPROPERTY(EditAnywhere, Category = "Trace")
	FName End;

	UPROPERTY(EditAnywhere, Category = "Trace")
	FName Rotation;

	UPROPERTY(EditAnywhere, Category = "Trace")
	double BoxCollisionLength{30.0};

	UPROPERTY(EditAnywhere, Category = "Trace")
	bool bDebugMode{false};

	TArray<AActor *> TargetsToIgnore;

public:
	// Sets default values for this component's properties
	UTraceComponent();

	UFUNCTION(BlueprintCallable, Category = "Trace")
	void HandleResetAttack();

	UPROPERTY(VisibleAnywhere, Category = "Trace")
	bool bIsAttacking{false};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void
	TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
