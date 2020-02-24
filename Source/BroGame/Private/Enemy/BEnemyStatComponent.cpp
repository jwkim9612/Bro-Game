// Fill out your copyright notice in the Description page of Project Settings.


#include "BEnemyStatComponent.h"
#include "BEnemyBase.h"

UBEnemyStatComponent::UBEnemyStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UBEnemyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBEnemyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBEnemyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	BMonster = Cast<ABEnemyBase>(GetOwner());
	BCHECK(BMonster != nullptr);

	InitMonsterData(BMonster);
}

void UBEnemyStatComponent::InitMonsterData(ABEnemyBase * Monster)
{
	BCHECK(Monster != nullptr);
	CurrentHP = Monster->GetMaxHP();
}

void UBEnemyStatComponent::SetHP(float NewHP)
{
	BCHECK(BMonster != nullptr);
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}
}

void UBEnemyStatComponent::SetHPToDamage(float Damage)
{
	BCHECK(BMonster != nullptr);
	SetHP(FMath::Clamp(CurrentHP - Damage, 0.0f, BMonster->GetMaxHP()));
}

float UBEnemyStatComponent::GetHP()
{
	return CurrentHP;
}

float UBEnemyStatComponent::GetHPRatio()
{
	return CurrentHP / BMonster->GetMaxHP();
}

int32 UBEnemyStatComponent::GetDamage()
{
	return BMonster->GetDamage();
}

int32 UBEnemyStatComponent::GetDropMoney()
{
	return BMonster->GetDropMoney();
}

