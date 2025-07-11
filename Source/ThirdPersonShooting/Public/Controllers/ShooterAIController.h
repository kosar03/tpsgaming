// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

private:


protected:
	virtual void BeginPlay() override;

private:
	APawn* PlayerPawn;

	// 靠近半径（厘米）。
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 300.f;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree; 
};
