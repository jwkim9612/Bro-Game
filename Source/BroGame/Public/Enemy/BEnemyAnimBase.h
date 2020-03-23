// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Animation/AnimInstance.h"
#include "BEnemyAnimBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitAttackDelegate);

/**
 * 
 */
UCLASS()
class BROGAME_API UBEnemyAnimBase : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;
	
	UFUNCTION()
	void AnimNotify_HitAttack();

public:
	void SetIsDead(bool IsDead); 
	void PlayAttackMontage();

public:
	FOnHitAttackDelegate OnHitAttack;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	class ABEnemyBase* Monster;

	UPROPERTY(BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	class ABPlayer* Target;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
