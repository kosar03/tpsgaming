// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (PlayerPawn) 
    {
        MoveToActor(PlayerPawn, 200);

    }

}

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)  
    {
        SetFocus(PlayerPawn);

    }
    
}