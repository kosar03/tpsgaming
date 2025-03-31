// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapons/Gun.h"
#include "Components/CapsuleComponent.h"
#include "GameModes/ShootingGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/CharacterMovementComponent.h"




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

	//设置角色动作组件的类变量
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bIgnoreBaseRotation = true;
	
	BasicGun = OverlapGun = nullptr;
	Health = MaxHealth;
	Alive = ALIVE;
	Shooting = UNSHOOTING;
	Reloading = UNRELOADING;
	Switching = UNSWITCHING;
	HasGun = HASNOGUN;
	Aiming = UNAIMING;

	
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	WalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	BasicGun = OverlapGun = nullptr;
	HasGun = HASNOGUN;
	Aiming = UNAIMING;
	Health = MaxHealth;
	Alive = ALIVE;
	Shooting = UNSHOOTING;
	Reloading = UNRELOADING;
	Switching = UNSWITCHING;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacter::MoveForward(float AxisValue)
{
	if (Controller && AxisValue)
	{
		// 找出向前方向
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 获取向前矢量
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	if (Controller && AxisValue)
	{
		// 找出向右方向
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 获取向右矢量
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 添加该方向动作
		AddMovementInput(Direction, AxisValue);
	}
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
	if (bCanJump) {
		Super::Jump();
		bCanJump = false;
		GetWorldTimerManager().SetTimer(JumpTimerHandle, this, &AShooterCharacter::JumpEnd, JumpDelay);
	}
}

void AShooterCharacter::JumpEnd()
{
	bCanJump = true;
	GetWorldTimerManager().ClearTimer(JumpTimerHandle);
}

bool AShooterCharacter::CanShoot()
{
	return HasGun && BasicGun && BasicGun->GetAmmoCount() && !Reloading && !Switching && !Shooting;
}

void AShooterCharacter::Shoot()
{
	if (CanShoot())
	{
		BasicGun->PullTrigger();
		Shooting = SHOOTING; 
	}
	else 
	{
		ShootEnd();
	}
}

void AShooterCharacter::ShootEnd()
{
	if (HasGun && BasicGun) 
    {
        BasicGun->PullTriggerEnd();
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

} 

void AShooterCharacter::WeaponSwitchNext()
{
	WeaponIndex = (WeaponIndex + 1) % EquippedGuns.Num();

}

void AShooterCharacter::Equip()
{
    if (OverlapGun)
    {	
		AGun* LastEquippedGun = BasicGun;
        if (BasicGun)
        {
			Reloading = UNRELOADING;
            DropEquippedGun();
        }
        EquipOverlapGun(LastEquippedGun);
        Switching = SWITCHING;
        if (Aiming) Aiming = UNAIMING;
        GetWorldTimerManager().SetTimer(SwitchingTimerHandle, this, &AShooterCharacter::EquipEnd, SwitchingDelay);
    }
}

void AShooterCharacter::EquipEnd()
{	
	Switching = UNSWITCHING;

}

void AShooterCharacter::DropEquippedGun()
{
	if (!HasGun && !BasicGun) 
	{
		return ;
	}
	BasicGun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	BasicGun->SetOwner(nullptr);
	BasicGun->SetEquipped(UNEQUIPPED);

	BasicGun = nullptr;
	HasGun = HASNOGUN;
}

void AShooterCharacter::EquipOverlapGun(AGun* LastEquippedGun)
{
	if (LastEquippedGun && LastEquippedGun->GetGunType() == OverlapGun->GetGunType())
	{
		OverlapGun->SetRemainingAmmoCount(LastEquippedGun->GetRemainingAmmoCount());
	}

	USoundBase* SwitchGunSound = OverlapGun->GetSwitchGunSound();
	if (SwitchGunSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SwitchGunSound, GetActorLocation());
	}

	BasicGun = OverlapGun;
	BasicGun->SetEquipped(EQUIPPED);
	BasicGun->GetSkeletalMeshComponent()->SetSimulatePhysics(false);
	BasicGun->SetActorLocation(FVector(0.f, 0.f, 0.f));
	BasicGun->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	FName SocketName = FName(*(BasicGun->GetGunName().ToString() + TEXT("Socket")));
	BasicGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
	BasicGun->SetOwner(this);

	SetEquippedGunCollision(BasicGun);
	EquippedGuns.Add(BasicGun);
	SetOverlapGun(nullptr);
	HasGun = HASGUN;

	if (LastEquippedGun)
	{
		SetDroppedGunCollision(LastEquippedGun);
	}
}

void AShooterCharacter::DropWeapon()
{
	SetDroppedGunCollision(BasicGun);
	DropEquippedGun();

	BasicGun = nullptr;
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

bool AShooterCharacter::CanReload()
{
	return BasicGun && BasicGun->GetRemainingAmmoCount() && BasicGun->GetFullAmmoCount() > BasicGun->GetAmmoCount() && !Reloading && !Switching && !Shooting;
}

void AShooterCharacter::Reload()
{
	if (CanReload())
	{
		BasicGun->SetRemainingAmmoCount(BasicGun->GetAmmoCount() + BasicGun->GetRemainingAmmoCount());
		int32 DeltaAmmoCount = FMath::Min(BasicGun->GetRemainingAmmoCount(), BasicGun->GetFullAmmoCount());
		BasicGun->SetRemainingAmmoCount(BasicGun->GetRemainingAmmoCount() - DeltaAmmoCount);
		BasicGun->SetAmmoCount(DeltaAmmoCount);	
		Reloading = RELOADING;
		if (Aiming) Aiming = UNAIMING;
		BasicGun->Reload();
		GetWorldTimerManager().SetTimer(ReloadingTimerHandle, this, &AShooterCharacter::ReloadEnd, BasicGun->GetReloadingDelay());
	}
}

void AShooterCharacter::ReloadEnd()
{
	if (BasicGun) 
	{
		Reloading = UNRELOADING;
	}
}


bool AShooterCharacter::CanAim()
{
	return HasGun && BasicGun && !Reloading && !Switching;
}

void AShooterCharacter::Aim()
{
	if (CanAim())
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->MaxWalkSpeed = AimSpeed;
		Aiming = AIMING;
	}
}

void AShooterCharacter::AimEnd()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	Aiming = UNAIMING;
}

void AShooterCharacter::SetEquippedGunCollision(AGun* EquippedGun)
{
	if (!EquippedGun) return;
	EquippedGun->GetSkeletalMeshComponent()->SetSimulatePhysics(false);
	EquippedGun->GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EquippedGun->GetCollisionSphereComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
} 

void AShooterCharacter::SetDroppedGunCollision(AGun* DroppedGun)
{
	if (!DroppedGun) return;
	DroppedGun->GetSkeletalMeshComponent()->SetSimulatePhysics(true);
	DroppedGun->GetSkeletalMeshComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DroppedGun->GetCollisionSphereComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
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
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &AShooterCharacter::ShootEnd);
	PlayerInputComponent->BindAction(TEXT("Equip"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Equip);
	PlayerInputComponent->BindAction(TEXT("WeaponSwitchLast"), EInputEvent::IE_Pressed, this, &AShooterCharacter::WeaponSwitchLast);
	PlayerInputComponent->BindAction(TEXT("WeaponSwitchNext"), EInputEvent::IE_Pressed, this, &AShooterCharacter::WeaponSwitchNext);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("DropWeapon"), EInputEvent::IE_Pressed, this, &AShooterCharacter::DropWeapon);

	// 瞄准绑定已在蓝图中的设置
	// PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Aim);
	// PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AShooterCharacter::AimEnd);

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
				if (BasicGun)
				{
					SetDroppedGunCollision(BasicGun);
				}
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

int32 AShooterCharacter::GetGunType() const
{
	if (HasGun && BasicGun)
	{
		return BasicGun->GetGunType();
	}
	return -1;
}