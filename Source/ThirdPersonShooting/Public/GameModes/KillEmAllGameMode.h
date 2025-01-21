// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/ShootingGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AKillEmAllGameMode : public AShootingGameModeBase
{
	GENERATED_BODY()

public: 
	AKillEmAllGameMode();

	virtual void PawnKilled(APawn* PawnKilled) override;

};
