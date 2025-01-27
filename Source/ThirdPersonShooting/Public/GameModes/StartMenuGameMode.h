// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/ShootingGameModeBase.h"
#include "StartMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AStartMenuGameMode : public AShootingGameModeBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> StartMenuHUDClass;

	UPROPERTY()
	class UUserWidget* StartMenuHUD;

public:
	AStartMenuGameMode();

protected:
	virtual void BeginPlay() override;


};
