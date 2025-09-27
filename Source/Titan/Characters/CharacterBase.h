// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "Titan/Characters/TitanAttributeSet.h"
#include "CharacterBase.generated.h"


class AHitbox;

UCLASS()
class TITAN_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UFUNCTION()
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(Category = "Abilites|Melee")
	bool ActivateMeleeAbility(bool AllowRemoteActivation = true);

	UFUNCTION()
	void SetMeleeAbility();

	UFUNCTION()
	void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(Category = "Attributes")
	virtual float GetHealth() const;
	UFUNCTION(Category = "Attributes")
	virtual float GetMaxHealth() const;
	UFUNCTION(Category = "Attributes")
	virtual float GetSkillGuage() const;
	UFUNCTION(Category = "Attributes")
	virtual float GetMaxSkillGuage() const;

	UPROPERTY()
	AHitbox* Hitbox_L;
	UPROPERTY()
	AHitbox* Hitbox_R;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(EditDefaultsOnly)
	UTitanAttributeSet* AttributeSet;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities|Melee")
	TSubclassOf<class UGameplayAbility> MeleeAbility;

	UPROPERTY()
	FGameplayAbilitySpecHandle MeleeAbilitySpecHandle;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<AHitbox> HitboxClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffects;

	float CharacterLevel = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
