// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsLookAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBTDecorator_IsLookAtTarget : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsLookAtTarget();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
	bool IsLookAtTarget(AActor* ControllingPawn, AActor* Target) const;
};