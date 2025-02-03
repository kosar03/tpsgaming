// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Gun.h"
#include "GunType.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API ARifle : public AGun
{
	GENERATED_BODY()

public:
	ARifle();

	virtual void PullTrigger() override;
	virtual void PullTriggerEnd() override;
	virtual void CeaseFire() override;

protected:

};
