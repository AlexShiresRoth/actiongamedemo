// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature,
	UCombatComponent, OnAttackPerformedDelegate, float, Amount);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ACTIONGAMEDEMO_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<UAnimMontage *> AttackAnimations;

	ACharacter *CharacterRef;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	int ComboCounter{0};

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	bool bCanAttack{true};

	UPROPERTY(EditAnywhere, Category = "Combat")
	float StaminaCost{5.0f};

public:
	// Sets default values for this component's properties
	UCombatComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ComboAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HandleResetAttack();

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnAttackPerformedSignature OnAttackPerformedDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
