// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/PlayerState.h"
#include "BPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
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
	void InitPlayerData();
	void SetHP(int32 NewHP);
	void SetHPToDamage(int32 Damage);
	float GetHPRatio() const;
	int32 GetCurrentHP() const;
	int32 GetCurrentMaxHP() const;
	void AddMoney(int32 Money);
	int32 GetCurrentMoney() const;

	FOnHPChangedDelegate OnHPChanged;
	FOnMoneyChangedDelegate OnMoneyChanged;

private:
	UPROPERTY()
	class ABPlayer* BPlayer;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentAttack;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentMaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	int32 CurrentMoney;
};
