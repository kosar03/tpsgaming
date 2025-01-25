// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingGameModeBase();

	virtual void PawnKilled(APawn* PawnKilled);

	virtual void DecreaseEnemyCount();

protected:

};
