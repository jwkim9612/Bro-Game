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
	
	//UFUNCTION()
	//void AnimNotify_HitAttack();

	UFUNCTION()
	void AnimNotify_StartHit();

	UFUNCTION()
	void AnimNotify_EndHit();

public:
	void SetIsDead(bool IsDead); 
	void PlayAttackMontage();

public:
	FOnHitAttackDelegate OnHitAttack;

protected:
	UPROPERTY()
	class ABEnemyBase* Monster;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
