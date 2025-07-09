// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IInteractable.h"
#include "UObject/SoftObjectPtr.h"
#include "OpenLevel.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API AOpenLevel : public AActor, public IIInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOpenLevel();

	ACharacter* CharacterRef;
	AActor* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	TSoftObjectPtr<UWorld> LevelToLoad;

	UPROPERTY(BlueprintReadOnly, Category = "Overlap")
	bool bIsOverlapping = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleOpenLevel(AActor* InteractedActor);

	UFUNCTION(BlueprintCallable)
	void HandleOnBeginOverlapEvent(AActor* OverlappingActor);

	UFUNCTION(BlueprintCallable)
	void HandleOnEndOverlapEvent(AActor* OverlappingActor);
};
