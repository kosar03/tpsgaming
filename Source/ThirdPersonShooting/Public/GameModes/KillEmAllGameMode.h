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

	virtual void Tick(float DeltaTime) override;

	virtual void PawnKilled(APawn* PawnKilled) override;

	virtual void DecreaseEnemyCount() override;

	UFUNCTION()
	void SetEnemyCount(int32 NewEnemyCount);

	UFUNCTION(BlueprintPure)
	int32 GetEnemyCount() const;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	int32 GetOriginEnemyCount();

private:
	void EndGame(bool bIsPlayerWinner);

protected:
	UPROPERTY();
	int32 EnemyCount;

};
