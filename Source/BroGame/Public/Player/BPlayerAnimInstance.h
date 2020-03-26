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
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void PlayGroundAttackMontage();
	void JumptoNextAttackSection(int32 NewSection);
	FName GetAttackMontageSectionName(int32 Section);

	void SetIsDead(bool IsDead);

	FOnCanNextAttackDelegate OnCanNextAttack;
	FOnHitAttackDelegate OnHitAttack;

private:
	UFUNCTION()
	void AnimNotify_CanNextAttack();

	UFUNCTION()
	void AnimNotify_HitAttack();

private:
	UPROPERTY()
	class ABPlayer* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool IsInAir = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	bool IsFocusMode = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	Pressed PressKey;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "stat", meta = (AllowPrivateAccess = true))
	UAnimMontage* GroundAttackMontage;
};
