// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Gun.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Controllers/ShooterPlayerController.h"
#include "Characters/ShooterCharacter.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponet = CreateDefaultSubobject<USceneComponent>(TEXT("My RootComponet"));
	SetRootComponent(MyRootComponet);

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere Component"));
	CollisionSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);	
	CollisionSphereComponent->SetupAttachment(MyRootComponet);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->SetupAttachment(MyRootComponet);


}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, SkeletalMesh, TEXT("MuzzleFlashSocket"));

	FHitResult OutHit;
	FVector ShotPosition, ShotDirection;
	bool bHit = GunTrace(OutHit, ShotPosition, ShotDirection);
	if (bHit) 
	{
		// DrawDebugPoint(GetWorld(), OutHit.Location, 20.f, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutHit.Location);

		AActor* HitActor = OutHit.GetActor();
		if (HitActor) {
			FPointDamageEvent PointDamageEvent(Damage, OutHit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, PointDamageEvent, GetOwnerController(), this);
		}

	}

}


// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGun::BeginOverlapFunc);	
	CollisionSphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGun::EndOverlapFunc);	


}

bool AGun::GunTrace(FHitResult &HitResult, FVector& ShotPosition, FVector& ShotDirection)
{	
	AController* OwnerController = GetOwnerController();
	if (!OwnerController) {
		return false;
	}

	FVector StartLocation;
	FRotator StartRotation;
	OwnerController->GetPlayerViewPoint(StartLocation, StartRotation);
	// DrawDebugCamera(GetWorld(), StartLocation, StartRotation, 120, 2, FColor::Red, true);
	FVector EndLocation = StartLocation + StartRotation.Vector() * MaxRange;
	ShotPosition = StartLocation;
	// 射击方向，故取负值。
	ShotDirection = -StartRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);

	return bHit; 
}

AController *AGun::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) {
		return nullptr;
	}
	
	return OwnerPawn->GetController();
}

void AGun::BeginOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("玩家重叠！"));
	AShooterCharacter* OverlapCharacter = Cast<AShooterCharacter>(OtherActor);
	if (OverlapCharacter)
	{
		OverlapCharacter->SetOverlapGun(this);
		AShooterPlayerController* OverlapCharacterController = Cast<AShooterPlayerController>(OverlapCharacter->GetController());
		if (OverlapCharacterController)
		{
			OverlapCharacterController->ShowEquipHUD();
		}
	}

}

void AGun::EndOverlapFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("玩家不再重叠！"));
	AShooterCharacter* OverlapCharacter = Cast<AShooterCharacter>(OtherActor);
	if (OverlapCharacter)
	{	
		OverlapCharacter->ClearOverlapGun();
		AShooterPlayerController* OverlapCharacterController = Cast<AShooterPlayerController>(OverlapCharacter->GetController());
		if (OverlapCharacterController)
		{
			OverlapCharacterController->RemoveEquipHUD();
		}
	}
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


