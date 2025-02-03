// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SwitchingGunAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API USwitchingGunAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	USwitchingGunAnimNotify();

protected:
	virtual bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const;
	
};
