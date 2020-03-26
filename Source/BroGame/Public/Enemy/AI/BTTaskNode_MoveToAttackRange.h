// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTaskNode_MoveToAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBTTaskNode_MoveToAttackRange : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_MoveToAttackRange();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
	class ABEnemyBase* Enemy;

	UPROPERTY()
	class ABPlayer* Target;
};
