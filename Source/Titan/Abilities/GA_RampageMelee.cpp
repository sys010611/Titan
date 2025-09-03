// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_RampageMelee.h"
#include "Titan/Utils/Debug.h"

void UGA_RampageMelee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	int32 SectionName_Int = FMath::RandRange(0, 1);
	FString SectionName_Str = FString::FromInt(SectionName_Int);
	SectionName = FName(*SectionName_Str);
	D("%s", *SectionName_Str);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);
}
