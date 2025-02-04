// Fill out your copyright notice in the Description page of Project Settings.


#include "Legacies/AmmoDropBall.h"
#include "Characters/ShooterCharacter.h"
#include "Weapons/Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"



AAmmoDropBall::AAmmoDropBall()
{
    AmmoCount = 10; // Default ammo count
}

void AAmmoDropBall::BeginPlay()
{
    Super::BeginPlay();
}

void AAmmoDropBall::BallEffect(AActor* InstigatorBall, AActor *EffectActor)
{
    AShooterCharacter* EffectCharacter = Cast<AShooterCharacter>(EffectActor);
    if (!EffectCharacter) { return; }
    if (!EffectCharacter->IsHasGun() || !EffectCharacter->GetBasicGun()) { return; }
    if (EffectCharacter && EffectCharacter->IsHasGun())
    {
        AGun* BasicGun = EffectCharacter->GetBasicGun();
        if (BasicGun)
        {
            BasicGun->UpdateRemainingAmmoCount(AmmoCount);
        }
    }

    if (BallSound) 
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), BallSound, GetActorLocation());
    }
	InstigatorBall->Destroy();

}

