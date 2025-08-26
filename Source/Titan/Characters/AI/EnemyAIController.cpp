// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Titan/Utils/Debug.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTree);

	GetWorldTimerManager().SetTimerForNextTick([this]()
		{
			if (GetBlackboardComponent())
			{
				if (UGameplayStatics::GetPlayerCharacter(this, 0))
				{
					GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), UGameplayStatics::GetPlayerCharacter(this, 0));
					D("SET TARGET ACTOR")
				}
				else
					D("no Character")
			}
			else
				D("no blackboard")
		});
}
