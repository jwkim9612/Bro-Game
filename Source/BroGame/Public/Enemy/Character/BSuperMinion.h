// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BMonster.h"
#include "BSuperMinion.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABSuperMinion : public ABMonster
{
	GENERATED_BODY()
	
public:
	ABSuperMinion();

public:
	virtual void SetSize(float NewSize) override;

private:
	const float DefaultCapsuleHalfHeight = 100.0f;
	const float DefaultCpasuleRadius = 70.0f;
	const float DeafultMeshZLocation = -100.0f;
};
