// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceSetDistToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Titan/Utils/Debug.h"

UBTServiceSetDistToTarget::UBTServiceSetDistToTarget()
{
	NodeName = "Set Distance to Target";
}

void UBTServiceSetDistToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
	{
		if (AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TEXT("TargetActor"))))
		{
			if (AAIController* AIController = OwnerComp.GetAIOwner())
			{
				if (APawn* ControlledPawn = AIController->GetPawn())
				{
					float Dist = ControlledPawn->GetDistanceTo(TargetActor);
					D("DIST : %f", Dist);

					BB->SetValueAsBool(TEXT("IsInMeleeRange"), Dist <= MeleeRange);
				}
			}
		}
	}
	
}
