// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BulletMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API UBulletMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	UBulletMovementComponent();
	
	virtual FVector ComputeMoveDelta(const FVector& InVelocity, float DeltaTime) const;
};
