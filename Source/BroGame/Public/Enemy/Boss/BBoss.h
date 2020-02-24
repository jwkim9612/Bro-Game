// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BEnemyBase.h"
#include "BBoss.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABBoss : public ABEnemyBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
