// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"
#include "BPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ABEnemyBase* ControllingPawn = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
	{
		return false;
	}

	ABPlayer* Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIControllerBase::TargetKey));
	if (Target == nullptr)
	{
		return false;
	}

	float ControllingPawnCapsuleRadius = ControllingPawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
	float TargetCapsuleRadius = Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

	// GetDistanceTo�Լ��� �� ���Ͱ��� ��ġ���� ���̸� �������ش�. 
	// �׷��� ���Ϳ� �÷��̾��� ĸ��ũ�� ������ 2 ���� ���� �����ַ��ߴµ� Log�� ���� 
	// ���Ϳ� �÷��̾��� ĸ��ũ�⸦ ���� ���� ���� ���ͼ� �� ĸ��ũ�⸦ ���־���.
	float DistanceFromPawnToTarget = (Target->GetDistanceTo(ControllingPawn)) - (ControllingPawnCapsuleRadius + TargetCapsuleRadius);

	BLOG(Warning, TEXT("DistanceFromPawnToTarget = %f, GetAttackRange = %f"), DistanceFromPawnToTarget, ControllingPawn->GetAttackRange());

	bResult = (DistanceFromPawnToTarget <= ControllingPawn->GetAttackRange());
	return bResult;
}
