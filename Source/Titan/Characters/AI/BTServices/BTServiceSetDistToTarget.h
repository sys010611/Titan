// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceSetDistToTarget.generated.h"

/**
 * 
 */
UCLASS()
class TITAN_API UBTServiceSetDistToTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTServiceSetDistToTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	float MeleeRange;
};
