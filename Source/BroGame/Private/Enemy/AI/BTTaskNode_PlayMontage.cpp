// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_PlayMontage.h"
#include "BBoss.h"
#include "BAIControllerBase.h"
#include "BBossAnimInstance.h"

UBTTaskNode_PlayMontage::UBTTaskNode_PlayMontage()
{
	bNotifyTick = true;
	NodeName = TEXT("PlayMontage");
}

EBTNodeResult::Type UBTTaskNode_PlayMontage::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	bIsDone = false;

	ABBoss* BBoss = Cast<ABBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == BBoss)
		return EBTNodeResult::Failed;

	float DefaultCharacterSpeed = BBoss->GetCharacterMovement()->GetMaxSpeed();
	BBoss->GetCharacterMovement()->MaxWalkSpeed = 0.0f;
	
	float MontagePlayTime = BBoss->GetAnimInstance()->Montage_Play(Montage);

	GetWorld()->GetTimerManager().SetTimer(MontageEndTimerHandle, FTimerDelegate::CreateLambda([this, BBoss, DefaultCharacterSpeed]() -> void {
		BBoss->GetCharacterMovement()->MaxWalkSpeed = DefaultCharacterSpeed;
		bIsDone = true;
	}), MontagePlayTime, false);

	return EBTNodeResult::InProgress;
}

void UBTTaskNode_PlayMontage::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsDone)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
