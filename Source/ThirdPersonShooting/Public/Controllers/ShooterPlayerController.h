// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 *
 */
UCLASS()
class THIRDPERSONSHOOTING_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

// 函数：
public:
	AShooterPlayerController();

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;



protected:
	virtual void BeginPlay() override;

private:

// 变量：
public:

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass; 

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass; 

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUD;

	// 单位：秒。
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimerHandle;

};
