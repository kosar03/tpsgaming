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

	class USkeletalMeshComponent* GetPhysicalMesh() const;
	
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
	UPROPERTY()
	int32 Equipped; 

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* CollisionSphereComponent;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* MyRootComponet;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere);
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 10000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY()
	FVector AttachLocation;


};


