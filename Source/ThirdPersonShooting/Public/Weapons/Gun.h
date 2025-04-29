// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunState.h"
#include "GunType.h"
#include "Gun.generated.h"



UCLASS()
class THIRDPERSONSHOOTING_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PullTrigger();
	virtual void PullTriggerEnd();
	virtual void UpdateShootingState();
	virtual void GunShoot();


	UFUNCTION(BlueprintPure)
	class USphereComponent* GetCollisionSphereComponent() const;

	int32 GetEquipped() const;
	void SetEquipped(int32 NewEquipped);
	
	UFUNCTION(BlueprintPure)
	class USkeletalMeshComponent* GetSkeletalMeshComponent() const;

	FName GetGunName() const;

	UFUNCTION(BlueprintPure)
	int32 GetRemainingAmmoCount() const {return RemainingAmmoCount;}
	UFUNCTION(BlueprintCallable)
	void SetRemainingAmmoCount(int32 NewRemainingAmmoCount) { RemainingAmmoCount = NewRemainingAmmoCount; }
	UFUNCTION(BlueprintPure)
	int32 GetFullAmmoCount() const { return FullAmmoCount; }
	UFUNCTION(BlueprintCallable)
	void SetFullAmmoCount(int32 NewFullAmmoCount) { FullAmmoCount = NewFullAmmoCount; }
	UFUNCTION(BlueprintPure)
	int32 GetAmmoCount() const { return AmmoCount; }
	UFUNCTION(BlueprintCallable)
	void SetAmmoCount(int32 NewAmmoCount) { AmmoCount = NewAmmoCount; }

	UFUNCTION(BlueprintPure)
	int32 GetGunType() const {return GunType;}
	UFUNCTION(BlueprintCallable)
	void SetGunType(int32 NewGunType) { GunType = NewGunType; }
	float GetReloadingDelay() const { return ReloadingDelay; }

	void UpdateRemainingAmmoCount(int32 DeltaRemaingAmmoCount);

	class USoundBase* GetSwitchGunSound() const { return SwitchGunSound; }

	float GetDamage() const { return Damage; }

	AController* GetOwnerController() const;
	
	void Reload();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

public:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAttribute")
	float ReloadingDelay = 2.0f;

	UPROPERTY()
	int32 Equipped; 

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphereComponent;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* SwitchGunSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAttribute")
	FName GunName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAttribute")
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAttribute")
	float Damage = 10;

	// 每秒射击次数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunAttribute")
	float FireSpeed = 4.f;

	// 备用弹药数
	UPROPERTY(EditDefaultsOnly)
	int32 RemainingAmmoCount = 0;

	// 弹匣弹药数
	UPROPERTY(EditDefaultsOnly)
	int32 FullAmmoCount = 30;

	// 当前弹药数
	UPROPERTY(VisibleAnywhere)
	int32 AmmoCount = 30;

	UPROPERTY(VisibleAnywhere)
	int32 GunType = DEFAULTGUNTYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* FireAnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* ReloadAnimationMontage;

	FTimerHandle PullTriggerTimerHandle;
	FTimerHandle PullTriggerEndTimerHandle;
};

