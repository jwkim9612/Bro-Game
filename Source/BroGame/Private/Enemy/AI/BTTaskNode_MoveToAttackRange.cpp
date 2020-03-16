// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MoveToAttackRange.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"
#include "BPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_MoveToAttackRange::UBTTaskNode_MoveToAttackRange()
{
	NodeName = TEXT("MoveToAttackRange");
}

EBTNodeResult::Type UBTTaskNode_MoveToAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABEnemyBase* Enemy = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr)
	{
		BLOG(Warning, TEXT("Failed"));
		return EBTNodeResult::Failed;
	}

	AcceptableRadius = Enemy->GetAttackRange();
	ObservedBlackboardValueTolerance = AcceptableRadius * 0.95f;

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MoveToAttackRange::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ABEnemyBase* Enemy = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr)
	{
		return;
	}

	ABPlayer* Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIControllerBase::TargetKey));
	if (Target == nullptr)
	{
		return;
	}

	BLOG(Warning, TEXT("distance %f"), Enemy->GetDistanceTo(Target));

	BLOG(Warning, TEXT("Test"));
}
