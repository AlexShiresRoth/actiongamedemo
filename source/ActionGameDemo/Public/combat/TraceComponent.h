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

public:
	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FName Start;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FName End;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	FName Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	double BoxCollisionLength{30.0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace")
	bool bDebugMode{false};

public:
	// Called every frame
	virtual void
	TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
