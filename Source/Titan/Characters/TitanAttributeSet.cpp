// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UTitanAttributeSet::UTitanAttributeSet()
{
}

void UTitanAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(UTitanAttributeSet, Health);
	DOREPLIFETIME(UTitanAttributeSet, MaxHealth);
	DOREPLIFETIME(UTitanAttributeSet, SkillGuage);
	DOREPLIFETIME(UTitanAttributeSet, MaxSkillGuage);
}

void UTitanAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetSkillGuage(FMath::Clamp(GetSkillGuage(), 0.f, GetMaxSkillGuage()));
	}
}

void UTitanAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

}

void UTitanAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTitanAttributeSet, Health, OldHealth);
}

void UTitanAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTitanAttributeSet, MaxHealth, OldMaxHealth);
}

void UTitanAttributeSet::OnRep_SkillGuage(const FGameplayAttributeData& OldSkillGuage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTitanAttributeSet, SkillGuage, OldSkillGuage);
}

void UTitanAttributeSet::OnRep_MaxSkillGuage(const FGameplayAttributeData& OldMaxSkillGuage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTitanAttributeSet, MaxSkillGuage, OldMaxSkillGuage);
}
