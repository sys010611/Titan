// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAnimInstance.h"
#include "BossCharacter.h"
#include "KismetAnimationLibrary.h"

void UBossAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BossCharacter = Cast<ABossCharacter>(TryGetPawnOwner());
}

void UBossAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (BossCharacter)
	{
		Direction = UKismetAnimationLibrary::CalculateDirection(BossCharacter->GetVelocity(), BossCharacter->GetActorRotation());
	}
}
