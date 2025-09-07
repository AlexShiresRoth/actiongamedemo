// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/IIsGettingReadyToFire.h"
#include "CompanionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAMEDEMO_API UCompanionAnimInstance : public UAnimInstance, public IIIsGettingReadyToFire
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSpeed{0.0f};

	UFUNCTION(BlueprintCallable, Category= Animation)
	void UpdateSpeed();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInCombat{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGettingReadyToFire{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsReadyToFire{false};

	virtual void SetIsGettingReadyToFire_Implementation(const bool bShouldGetReadyToFire) override
	{
		bIsGettingReadyToFire = bShouldGetReadyToFire;
	}
};
