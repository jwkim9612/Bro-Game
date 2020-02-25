// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Character.h"
#include "BEnemyBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class BROGAME_API ABEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABEnemyBase();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void virtual Attack();
	void AttackCheck();
	float GetMaxHP() const;
	float GetDamage() const;
	float GetAttackRange() const;
	int32 GetDropMoney() const;
	bool IsAttacking() const;
	void SetDamage(float NewDamage);
	void SetMaxHP(float NewHP);
	void SetSpeed(float NewSpeed);
	void SetDropMoney(int32 NewDropMoney);

	class UBEnemyStatComponent* GetCurrentStat() const;

public:
	FOnAttackEndDelegate OnAttackEnd;

protected:
	void virtual Dead();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* AnimMontage, bool Interrupted);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float MaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float DefaultDamage;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	int32 DropMoney;

	UPROPERTY()
	class ABAIControllerBase* BAIController;

	//UPROPERTY()
	//class UBEnemyAnimBase* BEnemyAnimInstance;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY(VisibleAnywhere, Category = "stat")
	class UBEnemyStatComponent* CurrentStat;

	bool bIsDead = false;
	bool bIsAttacking = false;
};