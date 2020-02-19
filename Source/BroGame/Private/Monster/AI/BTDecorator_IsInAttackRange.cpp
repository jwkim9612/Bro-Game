// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "BMonster.h"
#include "BAIController.h"
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

	ABMonster* ControllingPawn = Cast<ABMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return false;

	ABPlayer* Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIController::TargetKey));
	if (Target == nullptr)
		return false;

	float ControllingPawnCapsuleRadius = ControllingPawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
	float TargetCapsuleRadius = Target->GetCapsuleComponent()->GetScaledCapsuleRadius();

	// GetDistanceTo함수는 두 액터간의 위치벡터 차이를 리턴해준다. 
	// 그래서 몬스터와 플레이어의 캡슐크기 나누기 2 해준 값을 더해주려했는데 Log를 찍어보면 
	// 몬스터와 플레이어의 캡슐크기를 서로 더한 값이 나와서 두 캡슐크기를 빼주었다.
	float DistanceFromPawnToTarget = (Target->GetDistanceTo(ControllingPawn)) - (ControllingPawnCapsuleRadius + TargetCapsuleRadius);

	bResult = (DistanceFromPawnToTarget <= ControllingPawn->GetAttackRange());
	return bResult;
}
