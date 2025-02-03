// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterState.h"
#include "ShooterCharacter.generated.h"



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
	void SetShooting(bool NewShooting) { Shooting = NewShooting; }

	UFUNCTION(BlueprintPure)
	bool IsReloading() const { return (bool)Reloading; }

	UFUNCTION(BlueprintPure)
	bool IsSwitching() const { return (bool)Switching; }

	UFUNCTION(BlueprintPure)
	bool IsHasGun() const { return (bool)HasGun; }

	UFUNCTION(BlueprintPure)
	bool IsAiming() const { return (bool)Aiming; }

	UFUNCTION(BlueprintCallable)
	void SetIsAiming(bool NewAiming) { Aiming = NewAiming; }

	UFUNCTION(BlueprintPure)
	int32 GetGunType() const;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

	virtual void ShooterJump();
	virtual bool CanShoot();
	virtual void Shoot();
	virtual void ShootEnd();
	virtual void ShooterCrouch();
	virtual void WeaponSwitchLast();
	virtual void WeaponSwitchNext();
	virtual void Equip();
	virtual void EquipEnd();

	void SetOverlapGun(class AGun* NewOverlapGun);
	void ClearOverlapGun();
	float GetHealth() const;
	void SetHealth(float NewHealth);
	void UpdateHealth(float DeltaHealth);
	int32 GetAlive() const;
	void SetAlive(int32 NewAlive);
	
	void DropEquippedGun();
	void EquipOverlapGun(class AGun* LastEquippedGun);
	bool CanReload();
	void Reload();
	void ReloadEnd();
	void DropWeapon();
	bool CanAim();
	void Aim();
	void AimEnd();

	class AGun* GetBasicGun() const { return BasicGun; }
	class AGun* GetOverlapGun() const { return OverlapGun; } 

	void SetEquippedGunCollision(class AGun* EquippedGun);
	void SetDroppedGunCollision(class AGun* DroppedGun);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

protected:
	UPROPERTY()
	int32 Alive;

	UPROPERTY()
	int32 Shooting;

	UPROPERTY()
	int32 Reloading;
	
	UPROPERTY()
	int32 Switching;

	UPROPERTY()
	int32 HasGun;

	UPROPERTY()
	int32 Aiming;

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

	// 单位：秒。
	UPROPERTY(EditAnywhere)
	float SwitchingDelay = 0.5f;

	FTimerHandle SwitchingTimerHandle;

	FTimerHandle ReloadingTimerHandle;

private:

};
