// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "StatsComponent.h"
#include "EStat.h"
#include "InventoryComponent.h"
#include "combat/CombatComponent.h"
#include "combat/TraceComponent.h"
#include "combat/BlockComponent.h"
#include "combat/Lockon_Component.h"
#include "PlayerActionsComponent.h"
#include "Animations/PlayerAnimInstance_USE.h"
#include "combat/EquipmentComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));

	LockonComp = CreateDefaultSubobject<ULockon_Component>(TEXT("Lockon Component"));

	CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat Component"));

	TraceComp = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace Component"));

	BlockComp = CreateDefaultSubobject<UBlockComponent>(TEXT("Block Component"));

	PlayerActionsComp = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("Player Actions Comp"));

	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));

	EquipmentComp = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment Component"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnimInstance = Cast<UPlayerAnimInstance_USE>(GetMesh()->GetAnimInstance());

	AbilitySystemComponent = GetAbilitySystemComponent();

	if (AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Ability System Component"));
		StatsAttributes = AbilitySystemComponent->GetSet<UStatsAttributesSet>();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float APlayerCharacter::GetDamage()
{
	float BaseDamage = 0;

	if (EquipmentComp)
	{
		if (FItemData* SwordItem = EquipmentComp->Equipment.Find(Sword))
		{
			BaseDamage += SwordItem->TypePair.TypeValue;
		}
	}

	bool bIsCrit = false;
	if (StatsComp)
	{
		BaseDamage += StatsComp->Stats[Strength] * FMath::RandRange(.5f, 1.2f);

		float Roll = FMath::FRand();
		if (Roll <= StatsComp->Stats[CritChance])
		{
			bIsCrit = true;
			BaseDamage *= StatsComp->Stats[CritMultiplier];
		}
	}

	if (bIsCrit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Critical Hit! %f"), BaseDamage);
		return BaseDamage;
	}

	float Damage = FMath::RandRange(StatsComp->Stats[Strength], BaseDamage);

	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);

	return Damage;
}

bool APlayerCharacter::HasEnoughStamina(const float Amount)
{
	return StatsComp->Stats[Stamina] >= Amount;
}

void APlayerCharacter::EndLockonWithActor(class AActor* Actor)
{
	if (Actor != LockonComp->CurrentTargetActor)
	{
		return;
	}
	if (Actor == LockonComp->CurrentTargetActor)
	{
		LockonComp->StopLockon();
	}
}

bool APlayerCharacter::CanTakeDamage(AActor* Opponent)
{
	if (PlayerAnimInstance->bIsBlocking)
	{
		return BlockComp->Check(Opponent);
	}

	if (PlayerActionsComp->bIsRollActive)
	{
		return false;
	}

	return true;
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerCharacter::GetEquipment()
{
	if (InventoryComp)
	{
		const TMap<TEnumAsByte<EEQuipmentSlot>, FItemData>& Equipped = InventoryComp->GetEquippedItems();

		for (const auto& Pair : Equipped)
		{
			FString SlotName = UEnum::GetValueAsString(Pair.Key);
			FString ItemID = Pair.Value.ID; // Assuming FItemData has an ID field
			UE_LOG(LogTemp, Warning, TEXT("Equipped -> Slot: %s | Item: %s"), *SlotName, *ItemID);
		}
	}
}

void APlayerCharacter::PlayHurtAnim(TSubclassOf<class UCameraShakeBase> CameraShakeTemplate)
{
	PlayAnimMontage(HurtAnimMontage);

	if (CameraShakeTemplate)
	{
		GetController<APlayerController>()->ClientStartCameraShake(CameraShakeTemplate);
	}
}

void APlayerCharacter::FocusOnUI(UUserWidget* WidgetToFocus)
{
	if (!WidgetToFocus)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(GetController<APlayerController>());

	if (!PlayerController)
	{
		return;
	}

	PlayerController->bShowMouseCursor = true;

	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(WidgetToFocus->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputMode);

	// Pause Game
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void APlayerCharacter::RestoreGameInput()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController<APlayerController>());

	if (!PlayerController)
	{
		return;
	}

	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly());

	UE_LOG(LogTemp, Warning, TEXT("Game unpaused"));

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void APlayerCharacter::HandleDeath()
{
	PlayAnimMontage(DeathAnim);
	DisableInput(GetController<APlayerController>());
}
