// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RandomWalk.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_RandomWalk::UBTTask_RandomWalk()
{
    NodeName = TEXT("Get Random Walk Location");
}

void UBTTask_RandomWalk::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

EBTNodeResult::Type UBTTask_RandomWalk::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }
    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn)
    {
        return EBTNodeResult::Failed;
    }
    FVector RandomLocation = AIPawn->GetActorLocation() + FMath::VRand() * 1000;

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }
    BlackboardComp->SetValueAsVector(GetSelectedBlackboardKey(), RandomLocation);
    return EBTNodeResult::Succeeded;
}
