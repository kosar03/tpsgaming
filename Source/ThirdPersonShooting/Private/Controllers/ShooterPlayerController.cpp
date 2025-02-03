// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



AShooterPlayerController::AShooterPlayerController()
{
    
}

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromParent();

    if (bIsWinner)
    {   
        // this指定拥有该Widget的类实例，方便在Widget中获取。
        UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen)
        {
            WinScreen->AddToViewport();
        }
    }
    else
    {
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen)
        {
            LoseScreen->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &AShooterPlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::ShowEquipHUD()
{
    if (EquipHUD) 
    {
        EquipHUD->AddToViewport();
    }
}

void AShooterPlayerController::RemoveEquipHUD()
{
    EquipHUD->RemoveFromParent();
}

void AShooterPlayerController::BeginPlay()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD) 
    {
        HUD->AddToViewport();
    }
    EquipHUD = CreateWidget(this, EquipHUDClass);

}
