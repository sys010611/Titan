// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Titan/Combat/HitInterface.h"
#include "CharacterBase.h"
#include "BossCharacter.generated.h"

class AHitbox;

UCLASS()
class TITAN_API ABossCharacter : public ACharacterBase,public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossCharacter();

	void SetStrafing(bool flag);
	void SetWalking(bool flag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChanged();

	UPROPERTY(EditDefaultsOnly)
	float RunSpeed;

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
