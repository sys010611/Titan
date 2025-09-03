// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "BossCharacter.generated.h"

UCLASS()
class TITAN_API ABossCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(Category = "Abilites|Melee")
	bool ActivateMeleeAbility(bool AllowRemoteActivation = true);

	void SetStrafing(bool flag);

	void SetWalking(bool flag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetMeleeAbility();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Melee")
	TSubclassOf<class UGameplayAbility> MeleeAbility;

	UPROPERTY()
	FGameplayAbilitySpecHandle MeleeAbilitySpecHandle;

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
