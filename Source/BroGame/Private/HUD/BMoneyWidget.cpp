// Fill out your copyright notice in the Description page of Project Settings.


#include "BMoneyWidget.h"
#include "BPlayerController.h"
#include "BPlayerState.h"
#include "Components/TextBlock.h"

void UBMoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABPlayerController* BPlayerController = Cast<ABPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (BPlayerController != nullptr)
	{
		BPlayerState = Cast<ABPlayerState>(BPlayerController->PlayerState);
		if (BPlayerState != nullptr)
		{
			BPlayerState->OnMoneyChanged.AddUObject(this, &UBMoneyWidget::Update);
		}
	}

	Update();
}

void UBMoneyWidget::Update()
{
	BCHECK(BPlayerState);
	Money = BPlayerState->GetCurrentMoney();

	FText Text = FText::FromString(FString::Printf(TEXT(": %d"), Money));
	MoneyText->SetText(Text);
}