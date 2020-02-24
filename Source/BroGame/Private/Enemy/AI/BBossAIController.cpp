// Fill out your copyright notice in the Description page of Project Settings.


#include "BBossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

ABBossAIController::ABBossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTObject(TEXT("BehaviorTree'/Game/AI/Boss/Boss_BehaviorTree.Boss_BehaviorTree'"));

	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBObject(TEXT("BlackboardData'/Game/AI/Boss/Boss_BlackboardData.Boss_BlackboardData'"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
}

void ABBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}