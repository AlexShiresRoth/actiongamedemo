// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AI/BTT_ChargeAttack.h"

EBTNodeResult::Type UBTT_ChargeAttack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    UE_LOG(LogTemp, Warning, TEXT("Charge Attack!!!!!!!!!!!!!!!!!"));
    return EBTNodeResult::Succeeded;
}
