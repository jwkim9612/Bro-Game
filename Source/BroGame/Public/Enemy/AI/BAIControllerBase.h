// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "AIController.h"
#include "BAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABAIControllerBase : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName DestinationPosKey;
	static const FName RandomPosKey;
	static const FName TargetKey;

	void virtual RunAI();
	void virtual StopAI();

protected:
	const FVector DestinationLocation = FVector(500.0f, 900.0f, 220.0f);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBlackboardData* BBAsset;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;
};
