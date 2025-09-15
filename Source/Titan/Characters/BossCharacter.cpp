// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BossMovementComponent.h"
#include "Titan/Utils/Debug.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "Titan/Combat/Hitbox.h"

// Sets default values
ABossCharacter::ABossCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UBossMovementComponent>(ACharacter::CharacterMovementComponentName)) // 커스텀 MovementComponent 사용
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RunSpeed = 1500.f;
	WalkSpeed = 1000.f;

	if (UCharacterMovementComponent* MV = GetCharacterMovement())
	{
		MV->MaxStepHeight = 500.f;
	}

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
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
}

void ABossCharacter::SetStrafing(bool flag)
{
	if (flag)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;

		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			AIController->SetFocus(UGameplayStatics::GetPlayerCharacter(this, 0));
		}
	}
	else
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			AIController->ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}

void ABossCharacter::SetWalking(bool flag)
{
	if (flag)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void ABossCharacter::SetMeleeAbility()
{
	if (!AbilitySystemComponent)
		return;

	MeleeAbilitySpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MeleeAbility));
}


UAbilitySystemComponent* ABossCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


bool ABossCharacter::ActivateMeleeAbility(bool AllowRemoteActivation)
{
	if (!AbilitySystemComponent || !MeleeAbilitySpecHandle.IsValid())
	{
		return false;
	}

	//D("Enemy TryActivateAbility");
	return AbilitySystemComponent->TryActivateAbility(MeleeAbilitySpecHandle);
}

// Called every frame
void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

