// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Melee.h"
#include "Titan/Utils/Debug.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Titan/Characters/CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Titan/Characters/BossCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"

void UGA_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	int32 SectionName_Int = FMath::RandRange(0, SectionCount - 1);
	FString SectionName_Str = FString::FromInt(SectionName_Int);
	SectionName = FName(*SectionName_Str);

	UGameplayAbility::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance())
	{
		FOnMontageEnded Ended;
		Ended.BindUObject(this, &ThisClass::OnMontageEnd);
		AnimInstance->Montage_SetEndDelegate(Ended, MontageToPlay);
	}

	//// Wait task
	//EventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
	//	this,
	//	EventTagToWaitFor,
	//	nullptr,
	//	false,
	//	true
	//);

	//EventTask->EventReceived.AddDynamic(this, &UGA_Melee::OnDamageEventReceived);
	//EventTask->ReadyForActivation();
	//EventTask->Activate();

	//D("Activating Event Task");
}


void UGA_Melee::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	if (IsActive())
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, bInterrupted);
	}
}

void UGA_Melee::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	//if (EventTask)
	//	EventTask->EndTask();
	//D("END ABILITY");
}
