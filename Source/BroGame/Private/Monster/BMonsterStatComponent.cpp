// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterStatComponent.h"
#include "BMonster.h"

UBMonsterStatComponent::UBMonsterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UBMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBMonsterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBMonsterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	BMonster = Cast<ABMonster>(GetOwner());
	BCHECK(BMonster != nullptr);

	InitMonsterData(BMonster);
}

void UBMonsterStatComponent::InitMonsterData(ABMonster * Monster)
{
	BCHECK(Monster != nullptr);
	CurrentHP = Monster->GetMaxHP();
}

void UBMonsterStatComponent::SetHP(float NewHP)
{
	BCHECK(BMonster != nullptr);
	CurrentHP = NewHP;
	OnHPChanged.Broadcast();

	if (CurrentHP <= 0.0f)
	{
		OnHPIsZero.Broadcast();
	}
}

void UBMonsterStatComponent::SetHPToDamage(float Damage)
{
	BCHECK(BMonster != nullptr);
	SetHP(FMath::Clamp(CurrentHP - Damage, 0.0f, BMonster->GetMaxHP()));
}

float UBMonsterStatComponent::GetHP()
{
	return CurrentHP;
}

float UBMonsterStatComponent::GetHPRatio()
{
	return CurrentHP / BMonster->GetMaxHP();
}

int32 UBMonsterStatComponent::GetAttack()
{
	return BMonster->GetAttack();
}

