// Fill out your copyright notice in the Description page of Project Settings.


#include "StopAndStartAI_NS.h"
#include "..\..\Public\AnimNotifies\StopAndStartAI_NS.h"
#include "BMonster.h"
#include "BAIController.h"
#include "AIModule/Classes/BrainComponent.h"

void UStopAndStartAI_NS::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	BMonster = Cast<ABMonster>(MeshComp->GetOwner());
	if (BMonster != nullptr)
	{
		BAIController = Cast<ABAIController>(BMonster->GetController());
		if (BAIController != nullptr)
		{
			BAIController->StopMovement();
			BAIController->BrainComponent->StopLogic(FString(TEXT("Stop by Attacked")));
		}
	}
}

void UStopAndStartAI_NS::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	BMonster = Cast<ABMonster>(MeshComp->GetOwner());
	if (BMonster != nullptr)
	{
		BAIController = Cast<ABAIController>(BMonster->GetController());
		if (BAIController != nullptr)
		{
			BAIController->BrainComponent->RestartLogic();
		}
	}
}
