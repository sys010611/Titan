// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanCharacter.h"
#include "Titan/Combat/Hitbox.h"
#include "AbilitySystemComponent.h"
#include "Titan/Utils/Debug.h"
#include "Titan/AnimNotifiers/ANS_Combo.h"
#include "Abilities/GameplayAbility.h"

// Sets default values
ATitanCharacter::ATitanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* ATitanCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ATitanCharacter::BeginPlay()
{
	Super::BeginPlay();

	
	if (HitboxClass)
	{
		Hitbox_L = GetWorld()->SpawnActor<AHitbox>(HitboxClass);

		if (Hitbox_L)
		{
			Hitbox_L->AttachMeshToSocket(GetMesh(), TEXT("Hitbox_L"));
			Hitbox_L->SetOwner(this);
			Hitbox_L->SetInstigator(this);
		}

		Hitbox_R = GetWorld()->SpawnActor<AHitbox>(HitboxClass);

		if (Hitbox_R)
		{
			Hitbox_R->AttachMeshToSocket(GetMesh(), TEXT("Hitbox_R"));
			Hitbox_R->SetOwner(this);
			Hitbox_R->SetInstigator(this);
		}
	}
}

void ATitanCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!AbilitySystemComponent)
		return;

	SetMeleeAbility();
}

void ATitanCharacter::SetMeleeAbility()
{
	if (!AbilitySystemComponent)
		return;

	MeleeAbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MeleeAbility));
}

bool ATitanCharacter::IsUsingMelee()
{
	FGameplayTagContainer TagContainer(FGameplayTag::RequestGameplayTag(TEXT("Combat.Melee.Attack")));
	TArray<UGameplayAbility*> ActiveAbilities;

	GetActiveAbilitiesWithTags(TagContainer, ActiveAbilities);

	return !ActiveAbilities.IsEmpty();
}

void ATitanCharacter::GetActiveAbilitiesWithTags(FGameplayTagContainer GameplayTagContainer, TArray<UGameplayAbility*>& ActiveAbilities)
{
	if (!AbilitySystemComponent)
		return;

	TArray<FGameplayAbilitySpec*> MatchingAbilities;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, MatchingAbilities);
	for (FGameplayAbilitySpec* Spec : MatchingAbilities)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();
		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(ActiveAbility);
		}
	}
}

bool ATitanCharacter::ActivateMeleeAbility(bool AllowRemoteActivation)
{
	if (!AbilitySystemComponent || !MeleeAbilitySpecHandle.IsValid())
	{
		return false;
	}

	//D("Player TryActivateAbility");
	return AbilitySystemComponent->TryActivateAbility(MeleeAbilitySpecHandle);
}

void ATitanCharacter::ExecuteMeleeAttack()
{
	if (IsUsingMelee())
	{
		D("IsUsingMelee");
		ExecuteNextCombo();
	}
	else
	{
		D("NOT IsUsingMelee");
		ActivateMeleeAbility(false);
	}
	
}

void ATitanCharacter::ExecuteNextCombo()
{
	if (CanCombo)
	{
		if (UAnimInstance* AnimInst = GetMesh()->GetAnimInstance())
		{
			UAnimMontage* CurrMontage = AnimInst->GetCurrentActiveMontage();
			FName CurrSection = AnimInst->Montage_GetCurrentSection();
			if (NextComboNotify) // null check
			{
				AnimInst->Montage_SetNextSection(CurrSection, NextComboNotify->NextSectionName, CurrMontage);
				CanCombo = false;
			}
		}
	}
}

// Called every frame
void ATitanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATitanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

