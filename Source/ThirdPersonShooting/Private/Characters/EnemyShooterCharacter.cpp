// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyShooterCharacter.h"
#include "Legacies/DropBall.h"



float AEnemyShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (!GetAlive() && !DropBall)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            DropBall = World->SpawnActor<ADropBall>(DropBallClass);
            DropBall->SetActorLocation(GetActorLocation());
        }
    }

    return DamageToApply;
}