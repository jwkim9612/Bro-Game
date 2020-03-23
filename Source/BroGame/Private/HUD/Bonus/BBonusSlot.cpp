// Fill out your copyright notice in the Description page of Project Settings.


#include "BBonusSlot.h"
#include "BHUDWidget.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "..\..\..\Public\HUD\Bonus\BBonusSlot.h"

#include "BGameInstance.h"
#include "BBonusManager.h"

void UBBonusSlot::NativeConstruct()
{
	Super::NativeConstruct();

	BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BPlayerContoller = Cast<ABPlayerController>(GetOwningPlayer());
	BPlayerState = Cast<ABPlayerState>(GetOwningPlayerState());

	BonusButton->OnClicked.AddDynamic(this, &UBBonusSlot::OnBonusButtonClicked);
}

void UBBonusSlot::Init(UBHUDWidget * HUDWidget)
{
	if (HUDWidget != nullptr)
	{
		BHUDWidget = HUDWidget;
	}
}

void UBBonusSlot::RandomUpdate()
{
	BCHECK(BGameInstance != nullptr);
	BonusInfo = BGameInstance->BBonusManager->GetRandomBonus();
	
	UpdateWidget();
}

void UBBonusSlot::RandomUpdateByRarelity(EBonusRarelity Rarelity)
{
	BCHECK(BGameInstance != nullptr);
	BonusInfo = BGameInstance->BBonusManager->GetRandomBonusByRarelity(Rarelity);

	UpdateWidget();
}

void UBBonusSlot::OnBonusButtonClicked()
{
	switch (BonusInfo.Type)
	{
	case EBonusType::MaxHP:
		BPlayerState->MaxHPUp(BonusInfo.BonusValue);
		break;
	case EBonusType::Money:
		BPlayerState->AddMoney(BonusInfo.BonusValue);
		break;
	case EBonusType::Speed:
		BPlayerState->SpeedUp(BonusInfo.BonusValue);
		break;
	case EBonusType::Combo:
		BPlayerState->ComboUp(BonusInfo.BonusValue);
		break;
	default:
		BLOG(Warning, TEXT("Error!"));
		break;
	}

	OnBonusClicked.Broadcast();
	BHUDWidget->PlayHideBonusAnimation();
	BPlayerContoller->SetPause(false);
	BPlayerContoller->SetClickMode(false);
}

void UBBonusSlot::UpdateBonusText()
{
	FString Name = BonusInfo.BonusName.ToString();
	int32 Value = BonusInfo.BonusValue;
	BonusText->SetText(FText::FromString(FString::Printf(TEXT("%s +%d"), *Name, Value)));
}

void UBBonusSlot::UpdateBonusImage()
{
	UTexture2D* BonusTexture = nullptr;

	switch (BonusInfo.Type)
	{
	case EBonusType::MaxHP:
		BonusTexture = BGameInstance->BBonusManager->GetMaxHPTexture();
		break;
	case EBonusType::Speed:
		BonusTexture = BGameInstance->BBonusManager->GetSpeedTexture();
		break;
	case EBonusType::Money:
		BonusTexture = BGameInstance->BBonusManager->GetMoneyTexture();
		break;
	case EBonusType::Combo:
		BonusTexture = BGameInstance->BBonusManager->GetComboTexture();
		break;
	}

	BCHECK(BonusTexture != nullptr);
	BonusImage->SetBrushFromTexture(BonusTexture);
}

void UBBonusSlot::UpdateColorByRarelity()
{
	FLinearColor Color;

	switch (BonusInfo.Rarelity)
	{
	case EBonusRarelity::Normal:
		Color = FLinearColor::Gray;
		break;
	case EBonusRarelity::Rare:
		Color = FLinearColor::Blue;
		break;
	case EBonusRarelity::Unique:
		Color = FLinearColor::Red;
		break;
	case EBonusRarelity::Legend:
		Color = FLinearColor::Yellow;
		break;
	}

	ColorByRarelity->SetBrushColor(Color);
}

void UBBonusSlot::UpdateWidget()
{
	UpdateBonusText();
	UpdateBonusImage();
	UpdateColorByRarelity();
}
