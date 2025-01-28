// Fill out your copyright notice in the Description page of Project Settings.


#include "Legacies/AmmoDropBall.h"
#include "Characters/ShooterCharacter.h"
#include "Weapons/Gun.h"



AAmmoDropBall::AAmmoDropBall()
{
    AmmoCount = 10; // Default ammo count
}

void AAmmoDropBall::BeginPlay()
{
    Super::BeginPlay();
}

void AAmmoDropBall::BallEffect(AActor *EffectActor)
{
    AShooterCharacter* EffectCharacter = Cast<AShooterCharacter>(EffectActor);
    if (EffectCharacter)
    {
        AGun* BasicGun = EffectCharacter->GetBasicGun();
        if (BasicGun)
        {
            BasicGun->UpdateRemainingAmmoCount(AmmoCount);
        }
    }

}
