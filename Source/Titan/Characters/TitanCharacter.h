// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Titan/Combat/HitInterface.h"
#include "CharacterBase.h"
#include "TitanCharacter.generated.h"

class AHitbox;
class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class TITAN_API ATitanCharacter : public ACharacterBase, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATitanCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect);

	UPROPERTY()
	bool CanCombo;

	UPROPERTY()
	bool CanDoFinisher;

	UPROPERTY()
	class UANS_Combo* NextComboNotify;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	void ExecuteMeleeAttack();

	void ExecuteNextCombo();

	bool IsUsingMelee();

	void GetActiveAbilitiesWithTags(FGameplayTagContainer Tags, TArray<UGameplayAbility*>& ActiveAbilities);

};
