// Fill out your copyright notice in the Description page of Project Settings.


#include "BAIControllerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

const FName ABAIControllerBase::DestinationPosKey(TEXT("DestinationPos"));
const FName ABAIControllerBase::PatrolPosKey(TEXT("PatrolPos"));
const FName ABAIControllerBase::TargetKey(TEXT("Target"));

void ABAIControllerBase::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(DestinationPosKey, DestinationLocation);
		if (!RunBehaviorTree(BTAsset))
		{
			BLOG(Warning, TEXT("Not Run BehaviorTree"));
		}
	}
}

void ABAIControllerBase::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
