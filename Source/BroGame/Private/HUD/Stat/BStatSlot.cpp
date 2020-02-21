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
	BPlayerState->OnMaxHPChanged.AddUObject(this, &UBStatSlot::OnStatChanged);
}

void UBStatSlot::InitData(struct FBStatInfo& StatInfo)
{
	CurrentStat = StatInfo.Stat;
	StatImage->SetBrushFromTexture(StatInfo.Image);

	CurrentAttack = BPlayerState->GetCurrentAttack();
	CurrentMaxHP = BPlayerState->GetCurrentMaxHP();
	// 스피드 추가.

	ChangeStatText();
}

void UBStatSlot::OnStatChanged()
{
	CurrentAttack = BPlayerState->GetCurrentAttack();
	CurrentMaxHP = BPlayerState->GetCurrentMaxHP();

	ChangeStatText();
}

void UBStatSlot::ChangeStatText()
{
	switch (CurrentStat)
	{
	case EStat::Attack:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("Attack : %d"), CurrentAttack)));
		break;
	case EStat::MaxHP:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("MaxHP : %d"), CurrentMaxHP)));
		break;
	case EStat::Speed:
		StatText->SetText(FText::FromString(FString::Printf(TEXT("Speed : %d"), CurrentSpeed)));
		break;
	default:

		break;
	}
}
