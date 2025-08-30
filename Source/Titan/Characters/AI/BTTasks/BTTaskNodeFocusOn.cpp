// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodeFocusOn.h"
#include "Titan/Utils/Debug.h"
#include "Titan/Characters/BossCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTTaskNodeFocusOn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (ABossCharacter* BossCharacter = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		BossCharacter->SetStrafing(true);
		BossCharacter->SetWalking(true);
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
