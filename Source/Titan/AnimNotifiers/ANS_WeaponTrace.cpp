// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_WeaponTrace.h"
#include "Titan/Characters/CharacterBase.h"
#include "Titan/Combat/Hitbox.h"
#include "Components/BoxComponent.h"

void UANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacterBase* Character = MeshComp->GetOwner<ACharacterBase>())
	{
		if(bEnableLeft && Character->Hitbox_L)
			Character->Hitbox_L->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		if (bEnableRight && Character->Hitbox_R)
			Character->Hitbox_R->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void UANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacterBase* Character = MeshComp->GetOwner<ACharacterBase>())
	{
		if (Character->Hitbox_L)
		{
			Character->Hitbox_L->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Character->Hitbox_L->IgnoreActors.Empty();
		}

		if (Character->Hitbox_R)
		{
			Character->Hitbox_R->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Character->Hitbox_R->IgnoreActors.Empty();
		}
	}
}
