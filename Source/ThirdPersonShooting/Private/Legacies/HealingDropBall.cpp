// Fill out your copyright notice in the Description page of Project Settings.


#include "Legacies/HealingDropBall.h"
#include "Characters/ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"


AHealingDropBall::AHealingDropBall()
{
    HealingCount = 20.f;
}

void AHealingDropBall::BallEffect(AActor* InstigatorBall, AActor* EffectActor)
{
    AShooterCharacter* EffectCharacter = Cast<AShooterCharacter>(EffectActor);
    if (!EffectCharacter) { return; }
    EffectCharacter->UpdateHealth(HealingCount);

    if (BallSound) 
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), BallSound, GetActorLocation());
    }
	InstigatorBall->Destroy();
}

void AHealingDropBall::BeginPlay()
{
    Super::BeginPlay();

}
