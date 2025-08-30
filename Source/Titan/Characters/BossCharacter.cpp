// Fill out your copyright notice in the Description page of Project Settings.


#include "BossCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BossMovementComponent.h"
#include "Titan/Utils/Debug.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

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
}

// Called when the game starts or when spawned
void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABossCharacter::PerformMeleeAttack()
{
	PlayMeleeAttackAnimation();
}

void ABossCharacter::PlayMeleeAttackAnimation()
{
	D("PlayMeleeAttackAnimation");
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

