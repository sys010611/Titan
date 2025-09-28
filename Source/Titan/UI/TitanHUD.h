// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitanHUD.generated.h"

class UTitanOverlay;


UCLASS()
class TITAN_API ATitanHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	FORCEINLINE UTitanOverlay* GetTitanOverlay() { return TitanOverlay; };

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTitanOverlay> TitanOverlayClass;

	UPROPERTY()
	UTitanOverlay* TitanOverlay;
};
