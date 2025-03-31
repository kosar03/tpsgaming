// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/PoolActor.h"


// Sets default values
APoolActor::APoolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoolActor::BeginPlay()
{
	Super::BeginPlay();

	SetInUse(false);

	
}

// Called every frame
void APoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoolActor::SetInUse(bool InUse)
{
	this->bInUse = InUse;

	SetActorEnableCollision(InUse);
	SetActorHiddenInGame(!InUse);
	SetActorTickEnabled(InUse);
	GetWorldTimerManager().ClearTimer(LifeSpanTimer);

	if (InUse) 
	{
		GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &APoolActor::ReturnToPool, LifeSpanDelayTime, false);
	}
}

void APoolActor::ReturnToPool()
{
	SetInUse(false);
}