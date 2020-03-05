// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTaskNode_MoveToForSecond.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBTTaskNode_MoveToForSecond : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_MoveToForSecond();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Time")
	float MoveTime;

	FTimerHandle MoveTimerHandle;

	bool bIsDone = false;
};
