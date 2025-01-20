// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ClearBlackValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackValue::UBTTask_ClearBlackValue()
{
    NodeName = TEXT("Clear Blackboard Value");
}


EBTNodeResult::Type UBTTask_ClearBlackValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}