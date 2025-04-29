// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Rifle.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/ShooterCharacter.h"


ARifle::ARifle()
{
    GunName = TEXT("Rifle");

    GunType = RIFLE;

    FireSpeed = 4.f;
}

void ARifle::PullTrigger()
{
    Super::PullTrigger();
    AController* OOwnerController = GetOwnerController();
    if (OOwnerController) 
    {
        if (OOwnerController->IsPlayerController()) 
        {
            GetWorldTimerManager().SetTimer(PullTriggerTimerHandle, this, &ARifle::GunShoot, 1.f / FireSpeed, true);
        }
        else 
        {
            GetWorldTimerManager().SetTimer(PullTriggerTimerHandle, this, &ARifle::UpdateShootingState, 0.2f);
        }
    }
}

void ARifle::PullTriggerEnd()
{
    Super::PullTriggerEnd();
    
    AController* OOwnerController = GetOwnerController();
    if (OOwnerController) 
    {   
        if (OOwnerController->IsPlayerController()) 
        {
            GetWorldTimerManager().ClearTimer(PullTriggerTimerHandle);
            UpdateShootingState();
        }
    }
}

void ARifle::UpdateShootingState()
{
    Super::UpdateShootingState();
    
}

