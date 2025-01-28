// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Launcher.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"


ALauncher::ALauncher()
{
    GunName = TEXT("Launcher");

    GunType = 2;
}

void ALauncher::PullTrigger()
{
    Super::PullTrigger();

}
