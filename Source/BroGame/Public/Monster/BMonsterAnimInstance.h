// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimInstance.h"
#include "BMonsterAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitAttackDelegate);

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
	
public:
	void PlayAttackMontage();
	void PlayHitMontage();
	void SetIsDead(bool IsDead);

public:
	FOnHitAttackDelegate OnHitAttack;

private:
	UFUNCTION()
	void AnimNotify_HitAttack();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* HitMontage;


};
