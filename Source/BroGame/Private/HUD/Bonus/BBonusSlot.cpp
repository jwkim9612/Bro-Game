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

void UBBonusSlot::Update()
{
	BCHECK(BGameInstance != nullptr);
	BonusInfo = BGameInstance->BBonusManager->GetRandomBonus();
	
	UpdateBonusText();
	UpdateBonusImage();
	UpdateColorByRarelity();
}

void UBBonusSlot::OnBonusButtonClicked()
{
	switch (BonusInfo.Type)
	{
	case EBonusType::Attack:
		BPlayerState->AttackUp(BonusInfo.BonusValue);
		break;
	case EBonusType::MaxHP:
		BPlayerState->MaxHPUp(BonusInfo.BonusValue);
		break;
	case EBonusType::Money:
		BPlayerState->AddMoney(BonusInfo.BonusValue);
		break;
	case EBonusType::Speed:
		BPlayerState->SpeedUp(BonusInfo.BonusValue);
		break;
	}

	BHUDWidget->PlayHideBonusAnimation();
	BPlayerContoller->SetPause(false);
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
	case EBonusType::Attack:
		BonusTexture = BGameInstance->BBonusManager->GetAttackTexture();
		break;
	case EBonusType::MaxHP:
		BonusTexture = BGameInstance->BBonusManager->GetMaxHPTexture();
		break;
	case EBonusType::Speed:
		BonusTexture = BGameInstance->BBonusManager->GetSpeedTexture();
		break;
	case EBonusType::Money:
		BonusTexture = BGameInstance->BBonusManager->GetMoneyTexture();
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
