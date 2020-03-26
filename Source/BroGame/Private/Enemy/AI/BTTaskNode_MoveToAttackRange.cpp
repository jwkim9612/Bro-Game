// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MoveToAttackRange.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"
#include "BPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_MoveToAttackRange::UBTTaskNode_MoveToAttackRange()
{
	NodeName = TEXT("MoveToAttackRange");

	// Task�� ��������� ��� AI�� �����ϹǷ�
	// bCreateNodeInstance�� true�� ���������� �ν��Ͻ��� ���� ���鵵�� �ߴ�.
	// ó���� TickTask�� Enemy�� Target �ӽú����� ���������.
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskNode_MoveToAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Enemy = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy == nullptr)
	{
		BLOG(Warning, TEXT("Failed"));
		return EBTNodeResult::Failed;
	}

	Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIControllerBase::TargetKey));
	if (Target == nullptr)
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

	// ������ 10���� ���� -10�� ���־���.
	float Distance = Enemy->GetDistanceTo(Target) - 10;
	float CanAttackRange =
		Enemy->GetCapsuleComponent()->GetUnscaledCapsuleRadius() +
		Target->GetCapsuleComponent()->GetUnscaledCapsuleRadius() +
		Enemy->GetAttackRange();

	if (Distance < CanAttackRange)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
