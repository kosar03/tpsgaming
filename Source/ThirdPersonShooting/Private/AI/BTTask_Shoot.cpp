// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Shoot.h"
#include "Characters/ShooterCharacter.h"
#include "AIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

void UBTTask_Shoot::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) {
        return EBTNodeResult::Failed;
    }

    APawn* AIPawn = AIController->GetPawn();
    if (!AIPawn) {
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(AIPawn);
    if (!ShooterCharacter) {
        return EBTNodeResult::Failed;
    }

    ShooterCharacter->Shoot();
    return EBTNodeResult::Succeeded;

}
