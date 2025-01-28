// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

#ifndef EQUIPPED
#define EQUIPPED 1
#endif

#ifndef UNEQUIPPED
#define UNEQUIPPED 0
#endif


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

	UFUNCTION(BlueprintPure)
	class USphereComponent* GetCollisionSphereComponent() const;

	int32 GetEquipped() const;
	void SetEquipped(int32 NewEquipped);

	class UStaticMeshComponent* GetStaticMeshComponent() const;
	
	FName GetGunName() const;

	UFUNCTION(BlueprintPure)
	int32 GetRemainingAmmoCount() const {return RemainingAmmoCount;}
	UFUNCTION(BlueprintCallable)
	void SetRemainingAmmoCount(int32 NewRemainingAmmoCount) {RemainingAmmoCount = NewRemainingAmmoCount;}
	UFUNCTION(BlueprintPure)
	int32 GetFullAmmoCount() const {return FullAmmoCount;}
	UFUNCTION(BlueprintCallable)
	void SetFullAmmoCount(int32 NewFullAmmoCount) {FullAmmoCount = NewFullAmmoCount;}
	UFUNCTION(BlueprintPure)
	int32 GetAmmoCount() const {return AmmoCount;}
	UFUNCTION(BlueprintCallable)
	void SetAmmoCount(int32 NewAmmoCount) {AmmoCount = NewAmmoCount;}

	UFUNCTION(BlueprintPure)
	int32 GetGunType() const {return GunType;}
	UFUNCTION(BlueprintCallable)
	void SetGunType(int32 NewGunType) {GunType = NewGunType;}

	void UpdateRemainingAmmoCount(int32 DeltaRemaingAmmoCount);

	class USoundBase* GetSwitchGunSound() const { return SwitchGunSound; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool GunTrace(FHitResult& HitResult, FVector& ShotPosition, FVector& ShotDirection);

	AController* GetOwnerController() const;

	UFUNCTION()
	virtual void BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

public:

protected:
	UPROPERTY(VisibleAnywhere)
	FName GunName;

	UPROPERTY()
	int32 Equipped; 

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphereComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere);
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* SwitchGunSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY()
	FVector AttachLocation;

	UPROPERTY(EditDefaultsOnly)
	int32 RemainingAmmoCount = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 FullAmmoCount = 30;

	UPROPERTY(VisibleAnywhere)
	int32 AmmoCount = 30;

	UPROPERTY(VisibleAnywhere)
	int32 GunType = 0;

};


