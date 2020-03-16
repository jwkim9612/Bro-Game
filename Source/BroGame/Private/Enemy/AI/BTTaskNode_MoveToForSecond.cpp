// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_MoveToForSecond.h"
#include "BAIControllerBase.h"

UBTTaskNode_MoveToForSecond::UBTTaskNode_MoveToForSecond()
{
	bNotifyTick = true;
	NodeName = TEXT("MoveToForSecond");
}

EBTNodeResult::Type UBTTaskNode_MoveToForSecond::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	bIsDone = false;

	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
		bIsDone = true;
	}), MoveTime, false);

	BLOG(Warning, TEXT("radius %f, observed %f"), AcceptableRadius, ObservedBlackboardValueTolerance);


	return EBTNodeResult::InProgress;
}

void UBTTaskNode_MoveToForSecond::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsDone)
	{
		APawn* Pawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
		if (Pawn != nullptr)
		{
			Pawn->GetMovementComponent()->StopActiveMovement();
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
