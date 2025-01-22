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

    UE_LOG(LogTemp, Warning, TEXT("You Win!"));
    HUD->RemoveFromParent();

    if (bIsWinner)
    {   
        // this指定拥有该Widget的类实例，方便在Widget中获取。
        UUserWidget *WinScreen = CreateWidget(this, WinScreenClass);
        if (WinScreen)
        {
            UE_LOG(LogTemp, Warning, TEXT("添加Win Screen！"));
            WinScreen->AddToViewport();
        }
        else 
        {
            UE_LOG(LogTemp, Error, TEXT("WinScreen* 为nullptr！"));
        }
    }
    else
    {
        UUserWidget *LoseScreen = CreateWidget(this, LoseScreenClass);
        if (LoseScreen)
        {
            UE_LOG(LogTemp, Warning, TEXT("添加Lose Screen！"));
            LoseScreen->AddToViewport();
        }
        else 
        {
            UE_LOG(LogTemp, Error, TEXT("LoseScreen* 为nullptr！"));
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &AShooterPlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::BeginPlay()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD) 
    {
        UE_LOG(LogTemp, Warning, TEXT("添加HUD！"));
        HUD->AddToViewport();
    }
}
