// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick = true;

	// 한 몬스터가 공격을 마치면 다른 몬스터도 같이 마치는걸로 되기 때문에
	// 인스턴스를 하나씩 생성해줌
	bCreateNodeInstance = true;
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
