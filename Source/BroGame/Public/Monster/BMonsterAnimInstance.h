// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimInstance.h"
#include "BMonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;
};