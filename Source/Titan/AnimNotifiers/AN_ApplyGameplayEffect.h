// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_ApplyGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class TITAN_API UAN_ApplyGameplayEffect : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> GameplayEffect;
};
