// Fill out your copyright notice in the Description page of Project Settings.


#include "Legacies/HealingDropBall.h"
#include "Characters/ShooterCharacter.h"


AHealingDropBall::AHealingDropBall()
{
    HealingCount = 20.f;
}

void AHealingDropBall::BallEffect(AActor* EffectActor)
{
    AShooterCharacter* EffectCharacter = Cast<AShooterCharacter>(EffectActor);
    if (EffectCharacter)
    {
        EffectCharacter->UpdateHealth(HealingCount);
    }
}

void AHealingDropBall::BeginPlay()
{
    Super::BeginPlay();

}
