// Fill out your copyright notice in the Description page of Project Settings.


#include "BUpgradeSlot.h"
#include "BUpgradeWindow.h"
#include "BPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UBUpgradeSlot::NativeConstruct()
{
	Super::NativeConstruct();

	BPlayerState = Cast<ABPlayerState>(GetOwningPlayerState());
	BCHECK(BPlayerState != nullptr);
}

void UBUpgradeSlot::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (BPlayerState->GetCurrentMoney() >= CurrentPrice)
	{
		UpgradeButton->SetColorAndOpacity(FLinearColor::White);
		UpgradeButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		
		UpgradeButton->SetColorAndOpacity(FLinearColor::Gray);
		UpgradeButton->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UBUpgradeSlot::InitData(struct FBUpgradeInfo& UpgradeInfo)
{
	IncreaseStat = UpgradeInfo.IncreaseStat;
	IncreasePrice = UpgradeInfo.IncreasePrice;
	CurrentPrice = IncreasePrice;
	CurrentLevel = 1;
	CurrentStat = UpgradeInfo.Stat;

	UpgradeImage->SetBrushFromTexture(UpgradeInfo.Image);

	SetIncreaseStatText(IncreaseStat);
	SetPriceText(CurrentPrice);
	SetLevelText(CurrentLevel);

	if (UpgradeButton != nullptr)
	{
		UpgradeButton->OnClicked.AddDynamic(this, &UBUpgradeSlot::OnUpgradeButtonClicked);
	}
}

void UBUpgradeSlot::OnUpgradeButtonClicked()
{
	BPlayerState->UseMoney(CurrentPrice);

	CurrentPrice += IncreasePrice;
	SetPriceText(CurrentPrice);

	++CurrentLevel;
	SetLevelText(CurrentLevel);

	ChangeStat();
}

void UBUpgradeSlot::ChangeStat()
{
	switch (CurrentStat)
	{
	case EStat::Attack:
		BPlayerState->AttackUp(IncreaseStat);
		break;
	case EStat::MaxHP:
		BPlayerState->MaxHPUp(IncreaseStat);
		break;
	case EStat::Speed:

		break;
	default:

		break;
	}
}

void UBUpgradeSlot::SetIncreaseStatText(int32 Stat)
{
	switch (CurrentStat)
	{
	case EStat::Attack:
		IncreaseStatText->SetText(FText::FromString(FString::Printf(TEXT("Attack + %d"), Stat)));
		break;
	case EStat::MaxHP:
		IncreaseStatText->SetText(FText::FromString(FString::Printf(TEXT("MaxHP + %d"), Stat)));
		break;
	case EStat::Speed:
		IncreaseStatText->SetText(FText::FromString(FString::Printf(TEXT("Speed + %d"), Stat)));
		break;
	default:

		break;
	}
}

void UBUpgradeSlot::SetPriceText(int32 Price)
{
	PriceText->SetText(FText::FromString(FString::FromInt(Price)));
}

void UBUpgradeSlot::SetLevelText(int32 Level)
{
	LevelText->SetText(FText::FromString(FString::FromInt(Level)));
}
