// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnCanNextAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHitAttackDelegate);

#include "BroGame.h"
#include "Animation/AnimInstance.h"
#include "BPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBPlayerAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool IsInAir = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* GroundAttackMontage;

	UFUNCTION()
	void AnimNotify_CanNextAttack();

	UFUNCTION()
	void AnimNotify_HitAttack();

public:
	void PlayGroundAttackMontage();
	void JumptoNextAttackSection(int32 NewSection);
	FName GetAttackMontageSectionName(int32 Section);

	FOnCanNextAttackDelegate OnCanNextAttack;
	FOnHitAttackDelegate OnHitAttack;
};
