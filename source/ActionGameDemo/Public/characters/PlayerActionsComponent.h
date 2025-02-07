
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature,
	UPlayerActionsComponent,
	OnSprintDelegate,
	float, SprintCost);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter *CharacterRef;

	class IMainPlayer *IPlayerRef;

	class UCharacterMovementComponent *MovementComp;

	UPROPERTY(EditAnywhere)
	float SprintCost{0.1f};

	UPROPERTY(EditAnywhere)
	float SprintSpeed{1000.f};

	UPROPERTY(EditAnywhere)
	float WalkSpeed{500.f};

public:
	// Sets default values for this component's properties
	UPlayerActionsComponent();

	UPROPERTY(BlueprintAssignable, Category = "Player Actions")
	FOnSprintSignature OnSprintDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void Sprint();

	UFUNCTION(BlueprintCallable, Category = "Player Actions")
	void Walk();
};
