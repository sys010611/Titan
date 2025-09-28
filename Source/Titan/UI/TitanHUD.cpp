// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanHUD.h"
#include "TitanOverlay.h"

void ATitanHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController && TitanOverlayClass)
		{
			TitanOverlay = CreateWidget<UTitanOverlay>(PlayerController, TitanOverlayClass);
			TitanOverlay->AddToViewport(0);

			TitanOverlay->SetEnemyHealthBar(1.f);
			TitanOverlay->SetPlayerHealthBar(1.f);
		}
	}
}