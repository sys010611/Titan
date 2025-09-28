// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTitanOverlay::SetPlayerHealthBar(float Percent)
{
	if (HealthBar)
		HealthBar->SetPercent(Percent);
}

void UTitanOverlay::SetEnemyHealthBar(float Percent)
{
	if (EnemyHealthBar)
		EnemyHealthBar->SetPercent(Percent);
}