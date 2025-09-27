// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Titan/Utils/Debug.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Titan/Combat/Hitbox.h"
#include "Titan/Abilities/TitanAbilitySystemComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UTitanAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UTitanAttributeSet>(TEXT("AttributeSet"));

	CharacterLevel = 1;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SetMeleeAbility();

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

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	D("health : %f", AttributeSet->GetHealth());
	D("max health : %f", AttributeSet->GetMaxHealth());
	D("skill guage : %f", AttributeSet->GetSkillGuage());
	D("max skill guage : %f", AttributeSet->GetMaxSkillGuage());
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!AbilitySystemComponent)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffects, CharacterLevel, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveHandle = 
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::SetMeleeAbility()
{
	if (!AbilitySystemComponent)
		return;

	MeleeAbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MeleeAbility));
}

bool ACharacterBase::ActivateMeleeAbility(bool AllowRemoteActivation)
{
	if (!AbilitySystemComponent || !MeleeAbilitySpecHandle.IsValid())
	{
		return false;
	}

	//D("Enemy TryActivateAbility");
	return AbilitySystemComponent->TryActivateAbility(MeleeAbilitySpecHandle);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (AbilitySystemComponent)
		AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
}

float ACharacterBase::GetHealth() const
{
	if (!AttributeSet)
		return 0.f;

	return AttributeSet->GetHealth();
}

float ACharacterBase::GetMaxHealth() const
{
	if (!AttributeSet)
		return 0.f;

	return AttributeSet->GetMaxHealth();
}

float ACharacterBase::GetSkillGuage() const
{
	if (!AttributeSet)
		return 0.f;

	return AttributeSet->GetSkillGuage();
}

float ACharacterBase::GetMaxSkillGuage() const
{
	if (!AttributeSet)
		return 0.f;

	return AttributeSet->GetMaxSkillGuage();
}

