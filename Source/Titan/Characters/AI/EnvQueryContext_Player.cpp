// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryContext_Player.h"
#include "Kismet/GameplayStatics.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Titan/Characters/BossCharacter.h"
#include "Titan/Characters/AI/BossAIController.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	if (UWorld* World = GetWorld())
	{
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

		UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player); 
	}
}
