// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_Finisher.h"
#include "Titan/Characters/TitanCharacter.h"

void UANS_Finisher::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ATitanCharacter* TitanCharacter = MeshComp->GetOwner<ATitanCharacter>())
	{
		TitanCharacter->CanDoFinisher = true;

		// todo : 손이 빛나는 효과 등 타이밍 알기 쉽게 하기
	}
}

void UANS_Finisher::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ATitanCharacter* TitanCharacter = MeshComp->GetOwner<ATitanCharacter>())
	{
		TitanCharacter->CanDoFinisher = false;
	}
}
