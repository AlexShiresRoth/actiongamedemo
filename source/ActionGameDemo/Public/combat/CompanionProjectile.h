// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CompanionProjectile.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API ACompanionProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UParticleSystem* HitTemplate;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float ProjectileDamage{100.0f};

public:
	// Sets default values for this actor's properties
	ACompanionProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);

	UFUNCTION()
	void DestroyProjectile();

	UFUNCTION()
	void EndProjectileMovement(const float TimeDelay);
};
