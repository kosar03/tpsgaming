// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BlastRobotAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API UBlastRobotAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBlastRobotAnimInstance();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;
};
