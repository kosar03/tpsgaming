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

    UE_LOG(LogTemp, Warning, TEXT("You Lose!"));    
    
    UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
    if (LoseScreen) 
    {   
        UE_LOG(LogTemp, Warning, TEXT("添加Lose Screen！"));
        LoseScreen->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &AShooterPlayerController::RestartLevel, RestartDelay);
}
