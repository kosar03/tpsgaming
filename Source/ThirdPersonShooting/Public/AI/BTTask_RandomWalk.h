// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RandomWalk.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API UBTTask_RandomWalk : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_RandomWalk();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	
};
