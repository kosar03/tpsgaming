// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/StartMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AStartMenuGameMode::AStartMenuGameMode()
{

}

void AStartMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        StartMenuHUD = CreateWidget(PlayerController, StartMenuHUDClass);
    }
    if (StartMenuHUD)
    {
        PlayerController->GetPawn()->SetActorLocation(FVector(0.f, 0.f, 0.f));
        StartMenuHUD->AddToViewport();
        PlayerController->bShowMouseCursor = true;
    }


}