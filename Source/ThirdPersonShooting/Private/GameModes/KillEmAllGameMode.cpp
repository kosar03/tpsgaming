// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "Controllers/ShooterAIController.h"
#include "Characters/EnemyShooterCharacter.h"



AKillEmAllGameMode::AKillEmAllGameMode()
{

}

void AKillEmAllGameMode::Tick(float DeltaTime)
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

void AKillEmAllGameMode::DecreaseEnemyCount()
{   
    Super::DecreaseEnemyCount();

    SetEnemyCount(EnemyCount - 1);
}

void AKillEmAllGameMode::BeginPlay()
{
    int cnt = GetOriginEnemyCount();
    SetEnemyCount(cnt);
    UE_LOG(LogTemp, Warning, TEXT("初始敌人数目：%d"), cnt);
}

int32 AKillEmAllGameMode::GetOriginEnemyCount()
{
    auto Enemies = TActorRange<AEnemyShooterCharacter>(GetWorld());
    int32 cnt = 0;
    for (AEnemyShooterCharacter* Enemy : Enemies)
    {
        ++cnt;
    }
    return cnt;
}

void AKillEmAllGameMode::SetEnemyCount(int32 NewEnemyCount)
{
    EnemyCount = FMath::Max(0, NewEnemyCount);
}

int32 AKillEmAllGameMode::GetEnemyCount() const
{
    return EnemyCount;
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
