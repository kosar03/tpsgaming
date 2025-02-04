// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyShooterCharacter.h"
#include "Legacies/DropBall.h"
#include "Components/WidgetComponent.h"
#include "UIs/EnemyHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Math/UnrealMathUtility.h"
#include "Weapons/Gun.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



AEnemyShooterCharacter::AEnemyShooterCharacter()
{
    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Widget Component"));
    HealthWidgetComponent->SetupAttachment(RootComponent);
    HealthWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    HealthWidgetComponent->SetSimulatePhysics(false);

}

void AEnemyShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GetAlive())
    {
        UpdateHealthBarPercent();
    }
    else 
    {
        HealthWidgetComponent->SetVisibility(false);
    }
}

float AEnemyShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (!GetAlive())
    {
        UWorld* World = GetWorld();
        if (World)
        {
            ADropBall* DropBall = nullptr;
            float RandomValue = FMath::RandRange(0, 1000) / 1000.0f;
            if (RandomValue <= 0.3f)
            {
                DropBall = World->SpawnActor<ADropBall>(HealingBallClass);
            }  
            else 
            {
                DropBall = World->SpawnActor<ADropBall>(AmmoDropBallClass);
            }
            if (DropBall)
            {
                DropBall->SetActorLocation(GetActorLocation());
            }
        }
    }

    return DamageToApply;
}

void AEnemyShooterCharacter::UpdateHealthBarPercent()
{
    UProgressBar* HealthBar = GetHealthBar();
    if (HealthBar)
    {
        HealthBar->SetPercent(GetHealthPercent());
    }
}

UProgressBar* AEnemyShooterCharacter::GetHealthBar() const
{
    if (HealthWidgetComponent)
    {
        UUserWidget* HealthBarWidget = HealthWidgetComponent->GetUserWidgetObject();
        if (HealthBarWidget)
        {
            UEnemyHealthBarWidget* EnemyHealthBarWidget = Cast<UEnemyHealthBarWidget>(HealthBarWidget);
            if (EnemyHealthBarWidget)
            {
                return EnemyHealthBarWidget->GetHealthBar();
            }
        }
    }
    return nullptr;
}

void AEnemyShooterCharacter::BeginPlay()
{
    Super::BeginPlay();

    UWorld *World = GetWorld();
    BasicGun = World->SpawnActor<AGun>(GunClass);
    EquippedGuns.Add(BasicGun);
    WeaponIndex = 0;

    SetEquippedGunCollision(BasicGun);

    BasicGun->SetActorLocation(FVector(0.f, 0.f, 0.f));
    BasicGun->SetActorRotation(FRotator(0.f, 0.f, 0.f));
    FName SocketName = FName(*(BasicGun->GetGunName().ToString() + TEXT("Socket")));
    BasicGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, SocketName);
    BasicGun->SetOwner(this);

    
    BasicGun->SetEquipped(EQUIPPED);
    HasGun = HASGUN;
    Aiming = AIMING;

    GetCharacterMovement()->MaxWalkSpeed = 200.f;
    
    UpdateHealthBarPercent();
}