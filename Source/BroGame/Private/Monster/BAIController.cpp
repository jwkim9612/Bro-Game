// Fill out your copyright notice in the Description page of Project Settings.


#include "BAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Navigation/CrowdFollowingComponent.h"

const FName ABAIController::HomePosKey(TEXT("HomePos"));
const FName ABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ABAIController::TargetKey(TEXT("Target"));

ABAIController::ABAIController(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTObject(TEXT("BehaviorTree'/Game/AI/Monster_BehaviorTree.Monster_BehaviorTree'"));

	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBObject(TEXT("BlackboardData'/Game/AI/Monster_BlackboardData.Monster_BlackboardData'"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

}

void ABAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	MonsterPossessLocation = InPawn->GetActorLocation();
	RunAI();
}

void ABAIController::RunAI()
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, MonsterPossessLocation);
		if (!RunBehaviorTree(BTAsset))
		{
			BLOG(Warning, TEXT("Not Run BehaviorTree"));
		}
	}
}

void ABAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}
