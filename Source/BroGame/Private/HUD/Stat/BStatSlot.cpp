// Fill out your copyright notice in the Description page of Project Settings.


#include "BStatSlot.h"
#include "BPlayerState.h"
#include "BStatWindow.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "..\..\..\Public\HUD\Stat\BStatSlot.h"

void UBStatSlot::NativeConstruct()
{
	Super::NativeConstruct();

	BPlayerState = Cast<ABPlayerState>(GetOwningPlayerState());
	BCHECK(BPlayerState != nullptr);

	BPlayerState->OnAttackChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
	BPlayerState->OnDefenseChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
	BPlayerState->OnMaxHPChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
	BPlayerState->OnSpeedChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
	BPlayerState->OnCanComboChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
	//BPlayerState->OnStatChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
}

void UBStatSlot::InitData(struct FBStatInfo& StatInfo)
{
	CurrentStat = StatInfo.Stat;
	StatImage->SetBrushFromTexture(StatInfo.Image);

	OnStatChanged();
}

void UBStatSlot::OnStatChanged()
{
	switch (CurrentStat)
	{
	case EStat::Attack:
		CurrentAttack = BPlayerState->GetCurrentAttack();
		break;
	case EStat::Defense:
		CurrentDefense = BPlayerState->GetCurrentDefense();
		break;
	case EStat::MaxHP:
		CurrentMaxHP = BPlayerState->GetCurrentMaxHP();
		break;
	case EStat::Speed:
		CurrentSpeed = BPlayerState->GetCurrentSpeed();
		break;
	case EStat::Combo:
		CurrentCanCombo = BPlayerState->GetCurrentCanCombo();
		break;
	}

	ChangeStatText();
}

void UBStatSlot::ChangeStatText()
{
	switch (CurrentStat)
	{
	case EStat::Attack:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("Attack : %d"), CurrentAttack)));
		break;
	case EStat::Defense:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("Defense : %d"), CurrentDefense)));
		break;
	case EStat::MaxHP:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("MaxHP : %d"), CurrentMaxHP)));
		break;
	case EStat::Speed:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("Speed : %d"), CurrentSpeed)));
		break;
	case EStat::Combo:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("Combo : %d"), CurrentCanCombo)));
		break;
	}
}
