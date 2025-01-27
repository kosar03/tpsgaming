// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/Gun.h"
#include "Components/CapsuleComponent.h"
#include "GameModes/ShootingGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"



// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	
	Health = MaxHealth;
	Alive = ALIVE;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	UWorld *World = GetWorld();
	BasicGun = World->SpawnActor<AGun>(GunClass);
	EquippedGuns.Add(BasicGun);
	WeaponIndex = 0;

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	// GetMesh()->UnHideBoneByName(TEXT("weapon_r"));
	FName SocketName = FName(*(BasicGun->GetGunName().ToString() + TEXT("Socket")));
	BasicGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	BasicGun->SetOwner(this);
	BasicGun->GetStaticMeshComponent()->SetSimulatePhysics(false);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::ShooterJump()
{
	Super::Jump();
}

void AShooterCharacter::Shoot()
{
	if (BasicGun)
	{
		BasicGun->PullTrigger();
	}
}

void AShooterCharacter::ShooterCrouch()
{
	Super::Crouch(false);
}

void AShooterCharacter::WeaponSwitchLast()
{
	if (WeaponIndex == 0) 
	{
		WeaponIndex = EquippedGuns.Num() - 1;
	}
	else 
	{
		--WeaponIndex;
	}
	UE_LOG(LogTemp, Warning, TEXT("切换下一武器。"));
} 

void AShooterCharacter::WeaponSwitchNext()
{
	WeaponIndex = (WeaponIndex + 1) % EquippedGuns.Num();
	UE_LOG(LogTemp, Warning, TEXT("切换上一武器。"));
}

void AShooterCharacter::Equip()
{	
	if (OverlapGun)
	{
		if (BasicGun)
		{	
			DropEquippedGun();
		}
		EquipOverlapGun();
	}
	

}

void AShooterCharacter::SetOverlapGun(AGun* NewOverlapGun)
{
	OverlapGun = NewOverlapGun;
}

void AShooterCharacter::ClearOverlapGun()
{
	OverlapGun = nullptr;	
}

float AShooterCharacter::GetHealth() const 
{
	return Health;
}

void AShooterCharacter::SetHealth(float NewHealth)
{
	NewHealth = FMath::Min(MaxHealth, NewHealth);
	NewHealth = FMath::Max(0.f, NewHealth);
	Health = NewHealth;
}

void AShooterCharacter::UpdateHealth(float DeltaHealth)
{
	SetHealth(Health + DeltaHealth);
}

int32 AShooterCharacter::GetAlive() const
{
    return Alive;
}

void AShooterCharacter::SetAlive(int32 NewAlive)
{
	Alive = NewAlive;
}

void AShooterCharacter::EquipOverlapGun()
{
	BasicGun = OverlapGun;
	BasicGun->SetEquipped(EQUIPPED);
	BasicGun->GetStaticMeshComponent()->SetSimulatePhysics(false);
	BasicGun->SetActorLocation(FVector(0.f, 0.f, 0.f));
	BasicGun->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	FName SocketName = FName(*(BasicGun->GetGunName().ToString() + TEXT("Socket")));
	BasicGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	BasicGun->SetOwner(this);
	EquippedGuns.Add(BasicGun);
	SetOverlapGun(nullptr);
	UE_LOG(LogTemp, Error, TEXT("装备Gun！"));
}

void AShooterCharacter::DropEquippedGun()
{
	BasicGun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	BasicGun->SetOwner(nullptr);
	BasicGun->SetEquipped(UNEQUIPPED);
	BasicGun->GetStaticMeshComponent()->SetSimulatePhysics(true);
	UE_LOG(LogTemp, Error, TEXT("丢弃Gun！"));

}

 // Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ShooterJump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ShooterCrouch);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Equip"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Equip);
	PlayerInputComponent->BindAction(TEXT("WeaponSwitchLast"), EInputEvent::IE_Pressed, this, &AShooterCharacter::WeaponSwitchLast);
	PlayerInputComponent->BindAction(TEXT("WeaponSwitchNext"), EInputEvent::IE_Pressed, this, &AShooterCharacter::WeaponSwitchNext);

}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply * PhysicalShield;
	UE_LOG(LogTemp, Warning, TEXT("HP decrease!, left %f"), Health);

	if (IsDead())
	{	
		AShootingGameModeBase *GameMode = GetWorld()->GetAuthGameMode<AShootingGameModeBase>();
		if (GameMode)
		{
			if (GetAlive())
			{
				DropEquippedGun();
				GameMode->PawnKilled(this);
				GameMode->DecreaseEnemyCount();
				SetAlive(DEAD);
			}
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0.f;
}

float AShooterCharacter::GetHealthPercent() const
{
    return Health / MaxHealth;
}
