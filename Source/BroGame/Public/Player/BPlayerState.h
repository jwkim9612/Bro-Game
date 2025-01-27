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

// PlayerState 는 네트워크 게임에서 매우 유용한 클래스이다. 
// 이름에서 그 용도를 짐작할 수 있듯이 게임 플레이어의 모든 상태를 저장하고 다른 클라이언트에게 까지 전달할 수 있는 특징을 가지고 있다

// PlayerState 객체는 모든 클라이언트 머신과 서버 머신에서 공히 접근이 가능하며 
// 플레이어 하나에 한개의 PlayerState 가 할당되고 레벨이나 플레이어 폰(캐릭터)가 메모리에서 제거(Destroyed)되더라도 
// PlayerState 는 계속 존재하며 플레이어의 정보를 유지할 수 있다.

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
	void SetHPToRecoveryValue(int32 RecoveryValue);
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
