// Fill out your copyright notice in the Description page of Project Settings.


#include "BAIControllerBase.h"
#include "BGameStateBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

const FName ABAIControllerBase::DestinationPosKey(TEXT("DestinationPos"));
const FName ABAIControllerBase::RandomPosKey(TEXT("RandomPos"));
const FName ABAIControllerBase::TargetKey(TEXT("Target"));

void ABAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BCHECK(BGameStateBase);
}

void ABAIControllerBase::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(DestinationPosKey, DestinationLocation);
		if (!RunBehaviorTree(BTAsset))
		{
			BLOG(Warning, TEXT("Not Run BehaviorTree"));
		}
		else
		{
			bIsRunning = true;
		}
	}
}

void ABAIControllerBase::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
		bIsRunning = false;
	}
}
