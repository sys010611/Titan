// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodeMeleeAttack.h"
#include "Titan/Utils/Debug.h"
#include "Titan/Characters/BossCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTTaskNodeMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (ABossCharacter* BossCharacter = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		if (BossCharacter->ActivateMeleeAbility())
		{
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
