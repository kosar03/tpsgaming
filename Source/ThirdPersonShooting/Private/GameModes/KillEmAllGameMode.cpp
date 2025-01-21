// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/KillEmAllGameMode.h"



AKillEmAllGameMode::AKillEmAllGameMode()
{
    
}

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("A Pawn Was Killed!"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController) 
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
    
}
