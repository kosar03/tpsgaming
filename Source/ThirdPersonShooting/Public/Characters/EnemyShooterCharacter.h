// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ShooterCharacter.h"
#include "EnemyShooterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AEnemyShooterCharacter : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


};
