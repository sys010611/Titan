// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodeFocusOff.h"
#include "Titan/Utils/Debug.h"
#include "Titan/Characters/BossCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTTaskNodeFocusOff::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ABossCharacter* BossCharacter = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		BossCharacter->SetStrafing(false);
		BossCharacter->SetWalking(false);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
