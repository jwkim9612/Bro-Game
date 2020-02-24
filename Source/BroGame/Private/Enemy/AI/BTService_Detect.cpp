// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "BAIControllerBase.h"
#include "BPlayer.h"
#include "BEnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	ABEnemyBase* ControllingPawn = Cast<ABEnemyBase>(OwnerComp.GetAIOwner()->GetPawn());
	BCHECK(ControllingPawn != nullptr);

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();

	BCHECK(World != nullptr)
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	// ControllingPawn->IsAttacking()는 몬스터가 공격중에 몬스터와 플레이어가 멀어지면 공격 모션 그대로 도착지점으로 걸어가기 때문에 넣어줌
	if (bResult || ControllingPawn->IsAttacking())
	{
		for (auto& OverlapResult : OverlapResults)
		{
			auto Player = Cast<ABPlayer>(OverlapResult.GetActor());

			if (Player && Player->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABAIControllerBase::TargetKey, Player);
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABAIControllerBase::TargetKey, nullptr);
	}
}