// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Controllers/ShooterAIController.h"


AKillEmAllGameMode::AKillEmAllGameMode()
{
}

void AKillEmAllGameMode::PawnKilled(APawn *PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    UE_LOG(LogTemp, Warning, TEXT("A Pawn Was Killed!"));

    APlayerController *PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController)
    {
        EndGame(false);
        return ;
    }

    auto AIControllers = TActorRange<AShooterAIController>(GetWorld());
    for (AShooterAIController* AIController : AIControllers) 
    {
        if (!AIController->IsDead())
        {
            return ;
        }
    }
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    auto AControllers = TActorRange<AController>(GetWorld());
    for (AController* Controller : AControllers)
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
