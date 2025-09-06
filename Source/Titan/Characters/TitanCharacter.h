// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Titan/Combat/HitInterface.h"
#include "TitanCharacter.generated.h"

class AHitbox;

UCLASS()
class TITAN_API ATitanCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATitanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack();

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AHitbox> HitboxClass;

	UPROPERTY()
	AHitbox* Hitbox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
