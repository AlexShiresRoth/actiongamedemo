// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance_USE.generated.h"

/**
 *
 */
UCLASS()
class ACTIONGAMEDEMO_API UPlayerAnimInstance_USE : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Player Anim Instance")
	float CurrentSpeed{0.0f};

	UFUNCTION(BlueprintCallable, Category = "Player Anim Instance")
	void UpdateSpeed();

	UPROPERTY(BlueprintReadWrite, Category = "Player Anim Instance")
	bool bIsInCombat{false};

	UPROPERTY(BlueprintReadWrite, Category = "Player Anim Instance")
	float CurrentDirection{0.0f};

public:
	UFUNCTION(BlueprintCallable, Category = "Player Anim Instance")
	void HandleUpdatedTarget(AActor *NewTargetActorRef);

	UFUNCTION(BlueprintCallable, Category = "Player Anim Instance")
	void UpdateDirection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Anim Instance")
	bool bIsBlocking {false};
};
