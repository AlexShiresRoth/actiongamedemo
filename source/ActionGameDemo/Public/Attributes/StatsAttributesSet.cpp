// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/StatsAttributesSet.h"

#include "Net/UnrealNetwork.h"

UStatsAttributesSet::UStatsAttributesSet()
{
	Health.SetBaseValue(100.f);
	Health.SetCurrentValue(100.f);

	MaxHealth.SetBaseValue(100.f);
	MaxHealth.SetCurrentValue(100.f);
}

void UStatsAttributesSet::OnRep_Health(const FGameplayAttributeData& OldVal)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UStatsAttributesSet, Health, OldVal);
}

void UStatsAttributesSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UStatsAttributesSet, Health, COND_None, REPNOTIFY_Always);
}
