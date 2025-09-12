// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQuery_ValidEnemy.h"

#include "combat/CombatManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "Kismet/GameplayStatics.h"

void UEnvQuery_ValidEnemy::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	UWorld* World = QueryInstance.World;
	if (!World)
	{
		return;
	}

	ACombatManager* CombatManager = Cast<ACombatManager>(
		UGameplayStatics::GetActorOfClass(World, ACombatManager::StaticClass()));

	if (!CombatManager)
	{
		return;
	}

	const TArray<AActor*>& ValidEnemies = CombatManager->CombatTargets;

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ValidEnemies);
}
