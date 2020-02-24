// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BEnemyAnimBase.h"
#include "BMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBMonsterAnimInstance : public UBEnemyAnimBase
{
	GENERATED_BODY()
	
public:
	void PlayHitMontage();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* HitMontage;
};
