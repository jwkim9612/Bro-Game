// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TurnToTarget.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"
#include "BPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ABEnemyBase* ControllingPawn = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	ABPlayer* Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIControllerBase::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	// Turn할때 Yaw만 바뀌면 되기때문에 Yaw를 받아옴.
	float LookYaw = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), Target->GetActorLocation()).Yaw;
	FRotator LookAtRotation(0.0f, LookYaw, 0.0f);

	ControllingPawn->SetActorRotation(
		FMath::RInterpTo(
			ControllingPawn->GetActorRotation(),
			LookAtRotation,
			GetWorld()->GetDeltaSeconds(),
			2.0f
		)
	); 

	return EBTNodeResult::Succeeded;
}
