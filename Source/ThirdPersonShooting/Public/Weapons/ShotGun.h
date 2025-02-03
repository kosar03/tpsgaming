// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Gun.h"
#include "ShotGun.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API AShotGun : public AGun
{
	GENERATED_BODY()

public:
	AShotGun();

	virtual void PullTrigger() override;
	virtual void CeaseFire() override;

};
