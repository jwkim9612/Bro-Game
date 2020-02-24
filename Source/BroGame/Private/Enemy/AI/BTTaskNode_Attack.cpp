// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	bIsAttacking = true;

	ABEnemyBase* BEnemy = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BEnemy)
		return EBTNodeResult::Failed;
	BEnemy->Attack();

	BEnemy->OnAttackEnd.AddLambda([this]() ->void {
		bIsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
