// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Titan/Combat/HitInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "TitanCharacter.generated.h"

class AHitbox;
class UAbilitySystemComponent;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class TITAN_API ATitanCharacter : public ACharacter, public IHitInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATitanCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect);

	UPROPERTY()
	bool CanCombo;

	UPROPERTY()
	class UANS_Combo* NextComboNotify;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable)
	void ExecuteMeleeAttack();

	void ExecuteNextCombo();

	void SetMeleeAbility();

	UFUNCTION(Category = "Abilites|Melee")
	bool ActivateMeleeAbility(bool AllowRemoteActivation = true);

	bool IsUsingMelee();

	void GetActiveAbilitiesWithTags(FGameplayTagContainer Tags, TArray<UGameplayAbility*>& ActiveAbilities);

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AHitbox> HitboxClass;

	UPROPERTY()
	AHitbox* Hitbox_L;
	UPROPERTY()
	AHitbox* Hitbox_R;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Melee")
	TSubclassOf<class UGameplayAbility> MeleeAbility;

	UPROPERTY()
	FGameplayAbilitySpecHandle MeleeAbilitySpecHandle;

	float CharacterLevel = 0.f;

};
