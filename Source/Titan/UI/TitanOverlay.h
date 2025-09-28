// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitanOverlay.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class TITAN_API UTitanOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlayerHealthBar(float Percent);
	void SetEnemyHealthBar(float Percent);

protected:

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* EnemyHealthBar;
};
