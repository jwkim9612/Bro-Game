// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUDWidget.h"
#include "BGameStateBase.h"
#include "BPlayerState.h"
#include "BTimerWidget.h"
#include "BPlayerHPWidget.h"
#include "BUpgradeWidget.h"
#include "BStatWidget.h"

void UBHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABGameStateBase* BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameStateBase->OnCountDownStart.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Visible);
	});

	BGameStateBase->OnCountDownDone.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Hidden);
	});

	UpgradeWidget->Init();
	StatWidget->Init();
}

void UBHUDWidget::BindPlayerState(ABPlayerState * PlayerState)
{
	BCHECK(PlayerState != nullptr);

	CurrentPlayerState = PlayerState;
	PlayerState->OnHPChanged.AddUObject(this, &UBHUDWidget::UpdateHPWidget);
	PlayerState->OnMaxHPChanged.AddUObject(this, &UBHUDWidget::UpdateHPWidget);
}

void UBHUDWidget::UpdateHPWidget()
{
	HPBarWidget->SetHPBarPercent(CurrentPlayerState->GetHPRatio());
	HPBarWidget->SetHPText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), static_cast<float>(CurrentPlayerState->GetCurrentHP()), static_cast<float>(CurrentPlayerState->GetCurrentMaxHP()))));
}
