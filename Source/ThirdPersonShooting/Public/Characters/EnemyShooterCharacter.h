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
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthWidgetComponent;

public:
	AEnemyShooterCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateHealthBarPercent();

	class UProgressBar* GetHealthBar() const;

protected:
	virtual void BeginPlay() override;

};
