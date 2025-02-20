// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IInteractable.h"
#include "InteractableActor.generated.h"

//TODO need to render widget for item's inventory
UCLASS()
class ACTIONGAMEDEMO_API AInteractableActor : public AActor, public IIInteractable
{
	GENERATED_BODY()

	ACharacter* CharacterRef;
	AActor* PlayerRef;

public:
	// Sets default values for this actor's properties
	AInteractableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOverlapping{false};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HandleInteraction();

	UFUNCTION(BlueprintCallable)
	void HandleOnBeginOverlapEvent(AActor* OverlappingActor);

	UFUNCTION(BlueprintCallable)
	void HandleOnEndOverlapEvent(AActor* OverlappingActor);
};
