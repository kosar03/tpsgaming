// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API UEnemyHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	class UProgressBar* GetHealthBar() const { return HealthBar; }

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;


};
