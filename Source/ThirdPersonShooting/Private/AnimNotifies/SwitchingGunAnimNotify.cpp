// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SwitchingGunAnimNotify.h"
#include "Characters/ShooterCharacter.h"


USwitchingGunAnimNotify::USwitchingGunAnimNotify()
{

}


bool USwitchingGunAnimNotify::Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const 
{
    AShooterCharacter* OwnerCharacter = Cast<AShooterCharacter>(MeshComp->GetOwner());
    if (OwnerCharacter)
    {
        OwnerCharacter->SetIsAiming(false);
        return true;
    }
    return false;
}