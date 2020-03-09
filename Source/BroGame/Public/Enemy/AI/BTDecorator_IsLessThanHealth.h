// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsLessThanHealth.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBTDecorator_IsLessThanHealth : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsLessThanHealth();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const override;

private:
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 1.0f))
	float Percent;
};
