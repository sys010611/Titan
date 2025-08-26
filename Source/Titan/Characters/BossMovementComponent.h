// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BossMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class TITAN_API UBossMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UBossMovementComponent();
};
