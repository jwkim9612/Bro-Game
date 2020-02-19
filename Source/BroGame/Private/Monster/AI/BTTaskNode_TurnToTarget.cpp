// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TurnToTarget.h"
#include "BMonster.h"
#include "BAIController.h"
#include "BPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ABMonster* ControllingPawn = Cast<ABMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return EBTNodeResult::Failed;

	auto Target = Cast<ABPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	ControllingPawn->SetActorRotation(
		FMath::RInterpTo(
			ControllingPawn->GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), Target->GetActorLocation()),
			GetWorld()->GetDeltaSeconds(),
			2.0f
		)
	);

	return EBTNodeResult::Succeeded;
}
