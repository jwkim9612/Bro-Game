// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Character.h"
#include "BPlayer.generated.h"

UCLASS()
class BROGAME_API ABPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ABPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UTexture2D* GetTexture() const;
	FName GetName() const;

private:
	void SetControlMode();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Attack();
	void AttackCheck();
	void StartComboState();
	void EndComboState();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* AnimMontage, bool Interrupted);

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* Texture;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FName Name;

	UPROPERTY(EditDefaultsOnly, Category = "Combo", meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UBPlayerAnimInstance *BAnimInstance;

	FVector DirectionToMove = FVector::ZeroVector;

	bool bIsAttacking;
	bool OnComboInput;
	bool CanNextAttack;
	int32 CurrentCombo;
};
