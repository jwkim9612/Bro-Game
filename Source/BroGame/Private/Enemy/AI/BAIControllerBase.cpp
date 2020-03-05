// Fill out your copyright notice in the Description page of Project Settings.


#include "BAIControllerBase.h"
#include "BGameStateBase.h"
#include "BLevelScriptActor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

const FName ABAIControllerBase::DestinationPosKey(TEXT("DestinationPos"));
const FName ABAIControllerBase::RandomPosKey(TEXT("RandomPos"));
const FName ABAIControllerBase::TargetKey(TEXT("Target"));

void ABAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABGameStateBase* BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BCHECK(BGameStateBase);

	if (BGameStateBase->IsBossWave())
	{
		ABLevelScriptActor* BLevelScriptActor = Cast<ABLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (BLevelScriptActor != nullptr)
		{
			BLevelScriptActor->OnStartCinematic.AddLambda([this]() -> void {
				StopAI();
			});

			BLevelScriptActor->OnEndCinematic.AddLambda([this]() -> void {
				RunAI();
			});

		}
		else
		{
			BLOG(Warning, TEXT("No Controller"));
		}
	}
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
