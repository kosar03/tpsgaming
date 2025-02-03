// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/BulletMovementComponent.h"

UBulletMovementComponent::UBulletMovementComponent()
{

}

FVector UBulletMovementComponent::ComputeMoveDelta(const FVector &InVelocity, float DeltaTime) const
{
    Super::ComputeMoveDelta(InVelocity, DeltaTime);
    return FVector();
}
