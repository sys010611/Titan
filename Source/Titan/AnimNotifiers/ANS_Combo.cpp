// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Combo.h"
#include "Titan/Characters/TitanCharacter.h"

void UANS_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ATitanCharacter* TitanCharacter = Cast<ATitanCharacter>(MeshComp->GetOwner()))
	{
		TitanCharacter->CanCombo = true;
		TitanCharacter->NextComboNotify = this;
	}

	return;
}

void UANS_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ATitanCharacter* TitanCharacter = Cast<ATitanCharacter>(MeshComp->GetOwner()))
	{
		TitanCharacter->CanCombo = false;
	}

	return;
}
