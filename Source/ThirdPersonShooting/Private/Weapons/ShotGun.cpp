// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ShotGun.h"



AShotGun::AShotGun()
{
    GunType = SHOTGUN;
    GunName = TEXT("ShotGun");
    FullAmmoCount = 8;

    ReloadingDelay = 2.5f;
    FireSpeed = 1.f;

}

void AShotGun::PullTrigger()
{
    Super::PullTrigger();
    
    AController* OOwnerController = GetOwnerController();
    if (OOwnerController) 
    {
        if (OOwnerController->IsPlayerController()) 
        {
            GetWorldTimerManager().SetTimer(PullTriggerTimerHandle, this, &AShotGun::CeaseFire, 1.0f);
        }
    }
}

void AShotGun::CeaseFire()
{
    Super::CeaseFire();
}
