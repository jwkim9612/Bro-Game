// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BAIControllerBase.h"
#include "BBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABBossAIController : public ABAIControllerBase
{
	GENERATED_BODY()
	
public:
	ABBossAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
