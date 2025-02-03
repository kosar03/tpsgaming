// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Legacies/DropBall.h"
#include "AmmoDropBall.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AAmmoDropBall : public ADropBall
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 AmmoCount = 10;

public:
	AAmmoDropBall();

protected:
	virtual void BeginPlay() override;

	virtual void BallEffect(AActor* InstigatorBall, AActor* EffectActor) override;

};
