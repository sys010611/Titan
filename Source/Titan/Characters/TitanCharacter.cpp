// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanCharacter.h"
#include "Titan/Combat/Hitbox.h"

// Sets default values
ATitanCharacter::ATitanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATitanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (HitboxClass)
	{
		Hitbox = GetWorld()->SpawnActor<AHitbox>(HitboxClass);

		if (Hitbox)
		{
			Hitbox->AttachMeshToSocket(GetMesh(), TEXT("HitboxSocket"));
			Hitbox->SetOwner(this);
			Hitbox->SetInstigator(this);
		}
	}
}

void ATitanCharacter::Attack()
{
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

