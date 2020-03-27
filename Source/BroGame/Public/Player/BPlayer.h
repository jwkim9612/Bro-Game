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

	enum class AttackMode : uint8
	{
		Default,
		Boss,
		Focus
	};

public:
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UTexture2D* GetTexture() const;
	FName GetName() const;
	int32 GetDefaultAttack() const;
	int32 GetDefaultDefense() const;
	float GetDefaultMaxHP() const;
	int32 GetDefaultCanCombo() const;
	int32 GetMaxCombo() const;
	Pressed GetPressed() const;

	bool IsFocusing() const;
	bool IsDead() const;

private:
	void SetAttackMode(AttackMode NewAttackMode);

	void MoveUpDown(float AxisValue);
	void MoveRightLeft(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	void SetForwardBackwardPressedByValue(float AxisValue);
	void SetLeftRightPressedByValue(float AxisValue);
	void test();

	void Attack();
	void AttackCheck();
	void StartComboState();
	void EndComboState();

	void OnFocus();
	void OffFocus();

	void PlayParticle(UParticleSystem* ParticleSystem) const;
	void Dead();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* AnimMontage, bool Interrupted);

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;
	
	UPROPERTY()
	TArray<UCapsuleComponent*> AttackCollisions;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* Texture;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FName Name;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	int32 DefaultAttack;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	int32 DefaultDefense;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float DefaultMaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	int32 MaxCombo;

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	int32 DefaultCanCombo;

	UPROPERTY(EditDefaultsOnly, Category = "Particle", Meta = (AllowPrivateAccess = true))
	UParticleSystem* HitParticle;

	UPROPERTY()
	class UBPlayerAnimInstance *BAnimInstance;

	UPROPERTY()
	class ABPlayerController* BPlayerController;

	UPROPERTY()
	class UBGameInstance* BGameInstance;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY()
	class ABPlayerState* BPlayerState;

	FVector DirectionToMove = FVector::ZeroVector;

	float YawOfLookingDirection;
	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

	Pressed PressKey;
	FRotator FocusingRotation = FRotator(-30.0f, 0.0f, 0.0f);

	bool bFocus;
	bool bIsAttacking;
	bool OnComboInput;
	bool CanNextAttack;
	int32 CurrentCombo;
	AttackMode CurrentAttackMode;

	FTimerHandle BackToDefaultAttackModeTimerHandle;
	float BackToDefaultAttackModeTimer = 2.0f;

	bool bIsDead;
	FTimerHandle DeadTimerHandle;
	float DeadTimer = 3.0f;
};
