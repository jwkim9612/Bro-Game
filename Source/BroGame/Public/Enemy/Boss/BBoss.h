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

public:
	FName GetBossName() const;
	class UTexture2D* GetWantedPhoto() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "stat")
	FName BossName;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	class UTexture2D* WantedPhoto;
};
