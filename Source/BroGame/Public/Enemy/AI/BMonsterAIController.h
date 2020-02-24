// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BAIControllerBase.h"
#include "BMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABMonsterAIController : public ABAIControllerBase
{
	GENERATED_BODY()
	
public:
	ABMonsterAIController();//const FObjectInitializer& objectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
