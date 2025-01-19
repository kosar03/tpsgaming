// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerPawn)
    {
        if (LineOfSightTo(PlayerPawn))
        {
            // 以下采用行为树实现，故注释掉。
            // SetFocus(PlayerPawn);
            // 移动到玩家3米。
            // MoveToActor(PlayerPawn, AcceptanceRadius);

            // 行为树。
            GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation()); // 给黑板键设置值，是条件满足。
            GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
        }
        else
        {   // 以下采用行为树实现，故注释掉。
            // ClearFocus(EAIFocusPriority::Gameplay);
            // StopMovement();
            
            // 行为树。
            GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation")); // 给黑板键取消设置值，使条件不满足。

        }
    }
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