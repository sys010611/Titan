// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_SlowMotion.h"
#include "Titan/Characters/TitanCharacter.h"
#include "Kismet/GameplayStatics.h"

void UANS_SlowMotion::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UGameplayStatics::SetGlobalTimeDilation(MeshComp, StartTimeDilation);
}

void UANS_SlowMotion::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UGameplayStatics::SetGlobalTimeDilation(MeshComp, EndTimeDilation);
}
