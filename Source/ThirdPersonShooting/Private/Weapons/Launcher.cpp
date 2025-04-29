// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Launcher.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/ShooterCharacter.h"



ALauncher::ALauncher()
{
    GunName = TEXT("Launcher");

    GunType = SHOTGUN;

    ReloadingDelay = 5.0f;
    FireSpeed = 1.0f;
}

void ALauncher::PullTrigger()
{
    Super::PullTrigger();
    
    AController* OOwnerController = GetOwnerController();
    if (OOwnerController) 
    {
        if (OOwnerController->IsPlayerController()) 
        {
            GetWorldTimerManager().SetTimer(PullTriggerTimerHandle, this, &ALauncher::UpdateShootingState, 1.0f);
        }
    }
}

void ALauncher::UpdateShootingState()
{   
    Super::UpdateShootingState();

}