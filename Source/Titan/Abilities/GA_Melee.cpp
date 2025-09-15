// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Melee.h"
#include "Titan/Utils/Debug.h"

void UGA_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	D("ACTIVATE ABILITY");
	int32 SectionName_Int = FMath::RandRange(0, SectionCount-1);
	FString SectionName_Str = FString::FromInt(SectionName_Int);
	SectionName = FName(*SectionName_Str);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance())
	{
		FOnMontageBlendingOutStarted BlendOut;
		BlendOut.BindUObject(this, &ThisClass::OnMontageBlendOut_EndAbility);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendOut, MontageToPlay); // 
	}
}

void UGA_Melee::OnMontageBlendOut_EndAbility(UAnimMontage* Montage, bool bInterrupted)
{
	if (IsActive())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo,
			/*bReplicateEndAbility*/false, /*bWasCancelled*/bInterrupted);
	}
}


void UGA_Melee::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	D("END ABILITY");
}
