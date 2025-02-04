// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_UpdateMaxSpeed.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


UBTTask_UpdateMaxSpeed::UBTTask_UpdateMaxSpeed()
{

}

EBTNodeResult::Type UBTTask_UpdateMaxSpeed::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    ACharacter* AICharacter = Cast<ACharacter>(AIController->GetPawn());
    if (!AICharacter)
    {
        return EBTNodeResult::Failed;
    }

    AICharacter->GetCharacterMovement()->MaxWalkSpeed = 350.f;

    return EBTNodeResult::Succeeded;
}
