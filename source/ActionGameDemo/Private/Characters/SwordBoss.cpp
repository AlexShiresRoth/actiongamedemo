// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SwordBoss.h"

#include "AIController.h"
#include "Animations/BossAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"

// TODO - need a parent anim instance,to share setisblocking
void ASwordBoss::BeginPlay()
{
	Super::BeginPlay();

	if (BossBlackboardComponent)
	{
		BossBlackboardComponent->SetValueAsEnum("FightStages", FightStage);
	}
}

ASwordBoss::ASwordBoss()
{
	if (ControllerRef)
	{
		BossBlackboardComponent = ControllerRef->GetBlackboardComponent();
	}

	BlockComponent = CreateDefaultSubobject<UBlockComponent>(TEXT("BlockComponent"));
}

void ASwordBoss::PlayHurtAnimation()
{
	if (!HurtMontage || bIsDead) { return; }

	float AnimDuration{PlayAnimMontage(HurtMontage)};
}

bool ASwordBoss::CanTakeDamage(AActor* Opponent, UDamageType* DamageType)
{
	if (USkeletalMeshComponent* BossMesh = ControllerRef->GetCharacter()->GetMesh())
	{
		if (BossMesh)
		{
			if (BossMesh->GetAnimInstance())
			{
				if (UBossAnimInstance* BossAnim = Cast<UBossAnimInstance>(BossMesh->GetAnimInstance()))
				{
					if (BossAnim->GetIsBlocking())
					{
						if (BlockComponent->CheckEnemy(Opponent))
						{
							CharacterAudioComp->PlayDamageAudio();
							return true;
						}
						CharacterAudioComp->PlayBlockAudio();
						return false;
					}
				}
			}
		}
	}
	return true;
}
