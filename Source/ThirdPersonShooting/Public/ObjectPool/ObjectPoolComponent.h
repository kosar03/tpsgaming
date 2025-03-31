// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTING_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	void InitializePool();

	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	class APoolActor* GetFirstAvailableActor();

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "Object Pool")
	class APoolActor* SpawnFromPool(const FVector& Location, const FRotator& Rotation);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	TSubclassOf<class APoolActor> PoolActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	int32 PoolSize;

	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	TArray<class APoolActor*> PoolActors;

};
