// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

#ifndef DEAD
#define DEAD 0
#endif

#ifndef ALIVE
#define ALIVE 1
#endif

#ifndef SHOOTING
#define SHOOTING 1
#endif

#ifndef UNSHOOTING
#define UNSHOOTING 0
#endif


UCLASS()
class THIRDPERSONSHOOTING_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	bool IsShooting() const { return (bool)Shooting; }

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	void ShooterJump();
	void Shoot();
	void ShootEnd();
	void ShooterCrouch();
	void WeaponSwitchLast();
	void WeaponSwitchNext();
	void Equip();

	void SetOverlapGun(class AGun* NewOverlapGun);
	void ClearOverlapGun();
	float GetHealth() const;
	void SetHealth(float NewHealth);
	void UpdateHealth(float DeltaHealth);
	int32 GetAlive() const;
	void SetAlive(int32 NewAlive);
	void DropEquippedGun();
	void EquipOverlapGun();
	void Reload();

	class AGun* GetBasicGun() const { return BasicGun; }
	class AGun* GetOverlapGun() const { return OverlapGun; } 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY()
	int32 Alive;

	UPROPERTY()
	int32 Shooting;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class USpringArmComponent *CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	class UCameraComponent *FollowCamera;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY(BlueprintReadOnly)
	AGun* BasicGun;

	UPROPERTY(BlueprintReadOnly)
	AGun* OverlapGun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ADropBall> HealingBallClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ADropBall> AmmoDropBallClass;

	UPROPERTY(EditDefaultsOnly);
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float PhysicalShield = 1;

	TArray<class AGun*> EquippedGuns;

	int32 WeaponIndex = 0;

private:

};
