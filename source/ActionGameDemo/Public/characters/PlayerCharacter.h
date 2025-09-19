// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "Interfaces/Fighter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ACTIONGAMEDEMO_API APlayerCharacter : public ACharacter, public IMainPlayer, public IFighter,
                                            public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Player Animation")
	UAnimMontage* DeathAnim;

	UPROPERTY(EditAnywhere, Category = "Player Animation")
	UAnimMontage* HurtAnimMontage;

public:
	virtual FGenericTeamId GetGenericTeamId() const override
	{
		return FGenericTeamId(0);
	}

	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stats Component")
	class UStatsComponent* StatsComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Lockon Component")
	class ULockon_Component* LockonComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat Component")
	class UCombatComponent* CombatComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace Component")
	class UTraceComponent* TraceComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Block Component")
	class UBlockComponent* BlockComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Player Actions Comp")
	class UPlayerActionsComponent* PlayerActionsComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	class UInventoryComponent* InventoryComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Equipment")
	class UEquipmentComponent* EquipmentComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadonly, Category = "Player Character")
	class UPlayerAnimInstance_USE* PlayerAnimInstance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;

	virtual bool HasEnoughStamina(float Amount) override;

	virtual void EndLockonWithActor(class AActor* Actor) override;

	virtual bool CanTakeDamage(AActor* Opponent) override;

	UFUNCTION(BlueprintCallable)
	void GetEquipment();

	UFUNCTION(BlueprintCallable, Category = "Death")
	void HandleDeath();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void FocusOnUI(UUserWidget* WidgetToFocus);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RestoreGameInput();
};
