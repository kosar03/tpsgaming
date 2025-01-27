// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyShooterCharacter.h"
#include "Legacies/DropBall.h"
#include "Components/WidgetComponent.h"
#include "UIs/EnemyHealthBarWidget.h"
#include "Components/ProgressBar.h"



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

    if (!GetAlive() && !DropBall)
    {
        UWorld* World = GetWorld();
        if (World)
        {
            DropBall = World->SpawnActor<ADropBall>(DropBallClass);
            DropBall->SetActorLocation(GetActorLocation());
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

    UpdateHealthBarPercent();
}