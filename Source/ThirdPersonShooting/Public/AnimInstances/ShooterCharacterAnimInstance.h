 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTING_API UShooterCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float Angle;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float AimYaw;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	float AimPitch;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool IsCrouch;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool IsJump;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool IsDead;

	UPROPERTY(BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))	
	bool IsShooting;

public:
	UShooterCharacterAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

};
