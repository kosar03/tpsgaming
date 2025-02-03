// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Legacies/DropBall.h"
#include "HealingDropBall.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AHealingDropBall : public ADropBall
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	float HealingCount;

public:
	AHealingDropBall();	


protected:
	virtual void BeginPlay() override;

	virtual void BallEffect(AActor* InstigatorBall, AActor* EffectActor) override;
};
