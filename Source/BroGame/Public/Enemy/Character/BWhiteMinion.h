// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Monster/BMonster.h"
#include "BWhiteMinion.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABWhiteMinion : public ABMonster
{
	GENERATED_BODY()
	
public:
	ABWhiteMinion();

public:
	void virtual SetSize(float NewSize) override;

private:
	const float DefaultCapsuleHalfHeight = 60.0f;
	const float DefaultCpasuleRadius = 34.0f;
	const float DeafultMeshZLocation = -60.0f;
};
