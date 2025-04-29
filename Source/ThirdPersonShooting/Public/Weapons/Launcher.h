// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Gun.h"
#include "GunType.h"
#include "Launcher.generated.h"


/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API ALauncher : public AGun
{
	GENERATED_BODY()
	
public:
	ALauncher();

	virtual void PullTrigger() override;
	virtual void UpdateShootingState() override;
public:

protected:

private:


};
