// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolActor.generated.h"

UCLASS()
class THIRDPERSONSHOOTING_API APoolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	virtual void SetInUse(bool InUse);

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void ReturnToPool();
	
	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	bool bInUse;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	float LifeSpanDelayTime;

	FTimerHandle LifeSpanTimer;

};
