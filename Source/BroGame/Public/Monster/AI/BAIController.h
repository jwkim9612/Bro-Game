// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "AIController.h"
#include "BAIController.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABAIController();//const FObjectInitializer& objectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName DestinationPosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

	void RunAI();
	void StopAI();

private:
	UPROPERTY()
	UBehaviorTree* BTAsset;

	UPROPERTY()
	UBlackboardData* BBAsset;

	FVector DestinationLocation = FVector(500.0f, 900.0f, 220.0f);
};
