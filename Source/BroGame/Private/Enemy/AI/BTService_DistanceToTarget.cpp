// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DistanceToTarget.h"
#include "BPlayer.h"
#include "BAIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_DistanceToTarget::UBTService_DistanceToTarget()
{
	NodeName = TEXT("DistanceToTarget");
}

void UBTService_DistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	BCHECK(ControllingPawn != nullptr);

	ABPlayer* Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIControllerBase::TargetKey));
	BCHECK(Target != nullptr);;

	float DistanceToTarget = Target->GetDistanceTo(ControllingPawn);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(ABAIControllerBase::DistanceToTargetKey, DistanceToTarget);
}
