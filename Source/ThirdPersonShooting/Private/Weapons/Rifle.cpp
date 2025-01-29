// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Rifle.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"



ARifle::ARifle()
{
    GunName = TEXT("Rifle");

    GunType = 1;
}

void ARifle::PullTrigger()
{
    Super::PullTrigger();

}