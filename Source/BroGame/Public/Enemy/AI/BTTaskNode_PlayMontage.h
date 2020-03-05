// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBTTaskNode_PlayMontage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_PlayMontage();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* SpawnMontage;

	FTimerHandle MontageEndTimerHandle;

	bool bIsDone = false;
};
