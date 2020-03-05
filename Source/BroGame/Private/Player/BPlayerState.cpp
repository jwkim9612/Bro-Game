// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerState.h"
#include "BPlayerController.h"
#include "BPlayer.h"

void ABPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ABPlayerState::BeginPlay()
{
	Super::BeginPlay();

}

void ABPlayerState::InitPlayerData(APawn* Pawn)
{
	BCHECK(Pawn != nullptr);
	BPlayer = Cast<ABPlayer>(Pawn);
	BCHECK(BPlayer != nullptr);
	CurrentAttack = BPlayer->GetDefaultAttack();
	CurrentDefense = BPlayer->GetDefaultDefense();
	CurrentMaxHP = BPlayer->GetDefaultMaxHP();
	CurrentSpeed = BPlayer->GetCharacterMovement()->GetMaxSpeed();
	CurrentCanCombo = BPlayer->GetDefaultCanCombo();
	CurrentHP = CurrentMaxHP;
	CurrentMoney = 0;
}

void ABPlayerState::SetHP(int32 NewHP)
{
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();
}

void ABPlayerState::SetHPToDamage(int32 Damage)
{
	SetHP(FMath::Clamp(CurrentHP - Damage, 0, CurrentMaxHP));
}

float ABPlayerState::GetHPRatio() const
{
	return static_cast<float>(CurrentHP) / static_cast<float>(CurrentMaxHP);
}

int32 ABPlayerState::GetCurrentAttack() const
{
	return CurrentAttack;
}

int32 ABPlayerState::GetCurrentDefense() const
{
	return CurrentDefense;
}

int32 ABPlayerState::GetCurrentHP() const
{
	return CurrentHP;
}

int32 ABPlayerState::GetCurrentMaxHP() const
{
	return CurrentMaxHP;
}

int32 ABPlayerState::GetCurrentSpeed() const
{
	return CurrentSpeed;
}

int32 ABPlayerState::GetCurrentMoney() const
{
	return CurrentMoney;
}

int32 ABPlayerState::GetCurrentCanCombo() const
{
	return CurrentCanCombo;
}

void ABPlayerState::AttackUp(int32 IncreaseAttack)
{
	BCHECK(IncreaseAttack >= 0);
	CurrentAttack += IncreaseAttack;
	//OnStatChanged.Broadcast();
	OnAttackChanged.Broadcast();
}

void ABPlayerState::DefenseUp(int32 IncreaseDefense)
{
	BCHECK(IncreaseDefense >= 0);
	CurrentDefense += IncreaseDefense;
	//OnStatChanged.Broadcast();
	OnDefenseChanged.Broadcast();
}

void ABPlayerState::MaxHPUp(int32 IncreaseHP)
{
	BCHECK(IncreaseHP >= 0);
	CurrentMaxHP += IncreaseHP;
	//OnStatChanged.Broadcast();
	OnMaxHPChanged.Broadcast();
}

void ABPlayerState::SpeedUp(int32 IncreaseSpeed)
{
	BCHECK(IncreaseSpeed >= 0);
	CurrentSpeed += IncreaseSpeed;
	BPlayer->GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
	//OnStatChanged.Broadcast();
	OnSpeedChanged.Broadcast();
}

void ABPlayerState::ComboUp(int32 IncreaseCombo)
{
	BCHECK(IncreaseCombo >= 0);
	BCHECK(CurrentCanCombo + IncreaseCombo <= BPlayer->GetMaxCombo());
	CurrentCanCombo += IncreaseCombo;
	//OnStatChanged.Broadcast();
	OnCanComboChanged.Broadcast();
}

void ABPlayerState::AddMoney(int32 IncreaseMoney)
{
	BCHECK(IncreaseMoney > 0);
	CurrentMoney += IncreaseMoney;
	OnMoneyChanged.Broadcast();
}

void ABPlayerState::UseMoney(int32 UsedMoney)
{
	BCHECK(CurrentMoney >= UsedMoney);
	CurrentMoney -= UsedMoney;
	OnMoneyChanged.Broadcast();
}
