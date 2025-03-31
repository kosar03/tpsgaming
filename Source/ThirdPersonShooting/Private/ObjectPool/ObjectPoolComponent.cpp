// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/ObjectPoolComponent.h"
#include "ObjectPool/PoolActor.h"



// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	InitializePool();
	
}

void UObjectPoolComponent::InitializePool()
{
	if (!PoolActorClass) return;
	for (int32 i = 0; i < PoolSize; ++i)
	{
		APoolActor* PoolActor = GetWorld()->SpawnActor<APoolActor>(PoolActorClass, FVector::ZeroVector, FRotator::ZeroRotator);
		PoolActor->SetInUse(false);
		PoolActors.Add(PoolActor);
	}

}

APoolActor *UObjectPoolComponent::GetFirstAvailableActor()
{
	for (APoolActor* PoolActor : PoolActors)
	{
		if (!PoolActor->bInUse)
		{
			return PoolActor;
		}
	}
	return nullptr;
}

APoolActor *UObjectPoolComponent::SpawnFromPool(const FVector &Location, const FRotator &Rotation)
{
    APoolActor* PoolActor = GetFirstAvailableActor();
	if (PoolActor)
	{
		PoolActor->SetActorLocation(Location);
		PoolActor->SetActorRotation(Rotation);
		PoolActor->SetInUse(true);
	}
	return PoolActor;
}

// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

