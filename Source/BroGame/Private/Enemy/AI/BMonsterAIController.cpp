// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Navigation/CrowdFollowingComponent.h"

ABMonsterAIController::ABMonsterAIController()//const FObjectInitializer& objectInitializer)
	//: Super(objectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>
		BTObject(TEXT("BehaviorTree'/Game/AI/Monster/Monster_BehaviorTree.Monster_BehaviorTree'"));

	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData>
		BBObject(TEXT("BlackboardData'/Game/AI/Monster/Monster_BlackboardData.Monster_BlackboardData'"));

	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}
}

void ABMonsterAIController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
