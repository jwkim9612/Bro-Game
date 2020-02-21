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

	ABPlayerController* BPlayerController = Cast<ABPlayerController>(GetOwner());
	if (BPlayerController != nullptr)
	{
		BPlayer = Cast<ABPlayer>(BPlayerController->GetCharacter());
	}
}

void ABPlayerState::InitPlayerData()
{
	BCHECK(BPlayer != nullptr);
	CurrentAttack = BPlayer->GetDefaultAttack();
	CurrentMaxHP = BPlayer->GetDefaultMaxHP();
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

int32 ABPlayerState::GetCurrentHP() const
{
	return CurrentHP;
}

int32 ABPlayerState::GetCurrentMaxHP() const
{
	return CurrentMaxHP;
}

void ABPlayerState::AddMoney(int32 Money)
{
	BCHECK(Money > 0);
	CurrentMoney += Money;
	OnMoneyChanged.Broadcast();
}

void ABPlayerState::UseMoney(int32 Money)
{
	BCHECK(CurrentMoney >= Money);
	CurrentMoney -= Money;
	OnMoneyChanged.Broadcast();
}

int32 ABPlayerState::GetCurrentMoney() const
{
	return CurrentMoney;
}
