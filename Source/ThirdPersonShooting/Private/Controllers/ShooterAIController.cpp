// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ShooterCharacter.h"

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ShooterCharacter)
    {
        return ShooterCharacter->IsDead();
    }

    return true;
}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    // 玩家控制Pawn编号从0开始。
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if (AIBehaviorTree)
    {
        RunBehaviorTree(AIBehaviorTree);

        // 获取控制器所控制的Pawn。
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}