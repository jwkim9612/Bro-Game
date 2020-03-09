// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsLessThanHealth.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"
#include "BEnemyStatComponent.h"

UBTDecorator_IsLessThanHealth::UBTDecorator_IsLessThanHealth()
{
	NodeName = TEXT("LessThanHealth");
}

bool UBTDecorator_IsLessThanHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ABEnemyBase* ControllingPawn = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	float CurrentHPRatio = ControllingPawn->GetCurrentStat()->GetHPRatio();

	bResult = CurrentHPRatio <= Percent;

	return bResult;
}
