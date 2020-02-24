// Fill out your copyright notice in the Description page of Project Settings.


#include "StopAndStartAI_NS.h"
#include "BEnemyBase.h"
#include "BAIControllerBase.h"
#include "AIModule/Classes/BrainComponent.h"

void UStopAndStartAI_NS::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	BEnemy = Cast<ABEnemyBase>(MeshComp->GetOwner());
	if (BEnemy != nullptr)
	{
		BAIController = Cast<ABAIControllerBase>(BEnemy->GetController());
		if (BAIController != nullptr)
		{
			BAIController->StopMovement();
			BAIController->BrainComponent->StopLogic(FString(TEXT("Stop by Attacked")));
		}
	}
}

void UStopAndStartAI_NS::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	BEnemy = Cast<ABEnemyBase>(MeshComp->GetOwner());
	if (BEnemy != nullptr)
	{
		BAIController = Cast<ABAIControllerBase>(BEnemy->GetController());
		if (BAIController != nullptr)
		{
			BAIController->BrainComponent->RestartLogic();
		}
	}
}
