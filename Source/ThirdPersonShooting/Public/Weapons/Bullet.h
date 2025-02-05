// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class THIRDPERSONSHOOTING_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBulletHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void InitVelocity(const FVector& ShootDirection);

	void BulletDestroy();

	void BulletDestroyDelay();

	class UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void HitDetection();

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BulletMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	class UParticleSystem* TracerEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	class UParticleSystemComponent* TracerEffectComponent;

	UPROPERTY(EditAnywhere);
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditAnywhere)
	class USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly)
	float DestroyDelayTime = 3.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float HitDetectionDelayTime = 0.05f;

	FVector PreLocation;
	FVector CurrentLocation;

	FTimerHandle DestroyTimerHandle;
	FTimerHandle HitDetectionTimerHandle;

};
