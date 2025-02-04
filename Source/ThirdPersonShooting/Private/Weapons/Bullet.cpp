// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/DamageEvents.h"
#include "Weapons/Gun.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->SetSimulatePhysics(true);
	BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	BoxComponent->SetUseCCD(true);
	FBodyInstance* BodyInstance = BoxComponent->GetBodyInstance();
	if (BodyInstance)
	{
		BodyInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BodyInstance->SetUseCCD(true);
	}
	SetRootComponent(BoxComponent);

	BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh Component"));
	BulletMeshComponent->SetupAttachment(BoxComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 5678.f;
	ProjectileMovementComponent->MaxSpeed = 5678.f;
	ProjectileMovementComponent->bSweepCollision = true;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);

	if (TracerEffect)
	{
		TracerEffectComponent = UGameplayStatics::SpawnEmitterAttached(TracerEffect, BoxComponent, FName(), GetActorLocation(), GetActorRotation(), EAttachLocation::KeepWorldPosition);
	}


}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBulletHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit)
{
	FVector ShotDirection = -Hit.ImpactNormal;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

	AActor* HitActor = Hit.GetActor();
	if (HitActor) {
		AGun* OwnerGun = Cast<AGun>(GetOwner());
		if (OwnerGun)
		{
			FPointDamageEvent PointDamageEvent(OwnerGun->GetDamage(), Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(OwnerGun->GetDamage(), PointDamageEvent, OwnerGun->GetOwnerController(), this);
		}
	}
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABullet::InitVelocity(const FVector &ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABullet::BulletDestroyDelay()
{
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ABullet::BulletDestroy, DestroyDelayTime, false);
}

void ABullet::BulletDestroy()
{
	Destroy();
}
