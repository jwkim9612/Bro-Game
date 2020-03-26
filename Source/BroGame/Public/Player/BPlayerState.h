// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/PlayerState.h"
#include "BPlayerState.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnStatChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnDefenseChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMaxHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSpeedChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCanComboChangedDelegate);

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMoneyChangedDelegate);

// PlayerState �� ��Ʈ��ũ ���ӿ��� �ſ� ������ Ŭ�����̴�. 
// �̸����� �� �뵵�� ������ �� �ֵ��� ���� �÷��̾��� ��� ���¸� �����ϰ� �ٸ� Ŭ���̾�Ʈ���� ���� ������ �� �ִ� Ư¡�� ������ �ִ�

// PlayerState ��ü�� ��� Ŭ���̾�Ʈ �ӽŰ� ���� �ӽſ��� ���� ������ �����ϸ� 
// �÷��̾� �ϳ��� �Ѱ��� PlayerState �� �Ҵ�ǰ� �����̳� �÷��̾� ��(ĳ����)�� �޸𸮿��� ����(Destroyed)�Ǵ��� 
// PlayerState �� ��� �����ϸ� �÷��̾��� ������ ������ �� �ִ�.

/**
 * 
 */
UCLASS()
class BROGAME_API ABPlayerState : public APlayerState
{
	GENERATED_BODY()
		
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	void InitPlayerData(class APawn* Pawn);
	void SetHP(int32 NewHP);
	void SetHPToDamage(int32 Damage);
	float GetHPRatio() const;
	int32 GetCurrentAttack() const;
	int32 GetCurrentDefense() const;
	int32 GetCurrentHP() const;
	int32 GetCurrentMaxHP() const;
	int32 GetCurrentSpeed() const;
	int32 GetCurrentMoney() const;
	int32 GetCurrentCanCombo() const;
	void AttackUp(int32 IncreaseAttack);
	void DefenseUp(int32 IncreaseDefense);
	void MaxHPUp(int32 IncreaseHP);
	void SpeedUp(int32 IncreaseSpeed);
	void ComboUp(int32 IncreaseCombo);
	void AddMoney(int32 IncreaseMoney);
	void UseMoney(int32 UsedMoney);


	//FOnStatChangedDelegate OnStatChanged;
	FOnAttackChangedDelegate OnAttackChanged;
	FOnDefenseChangedDelegate OnDefenseChanged;
	FOnMaxHPChangedDelegate OnMaxHPChanged;
	FOnSpeedChangedDelegate OnSpeedChanged;
	FOnCanComboChangedDelegate OnCanComboChanged;

	FOnHPChangedDelegate OnHPChanged;
	FOnHPIsZeroDelegate OnHPIsZero;
	FOnMoneyChangedDelegate OnMoneyChanged;

private:
	UPROPERTY()
	class ABPlayer* BPlayer;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentAttack;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentDefense;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentMaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentMoney;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentSpeed;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentCanCombo;
};
