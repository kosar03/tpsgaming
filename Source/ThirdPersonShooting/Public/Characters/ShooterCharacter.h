// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class THIRDPERSONSHOOTING_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent *CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class UCameraComponent *FollowCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	AGun* BasicGun;

	UPROPERTY()
	AGun* OverlapGun;

	UPROPERTY(EditDefaultsOnly);
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float PhysicalShield = 1;

	TArray<class AGun*> EquippedGuns;

	int32 WeaponIndex = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	void ShooterJump();
	void Shoot();
	void ShooterCrouch();
	void WeaponSwitchLast();
	void WeaponSwitchNext();
	void Equip();

	void SetOverlapGun(AGun* NewOverlapGun);
	void ClearOverlapGun();
	float GetHealth();

private:

};
