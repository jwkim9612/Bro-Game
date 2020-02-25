// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUDWidget.h"
#include "BGameStateBase.h"
#include "BPlayerState.h"
#include "BTimerWidget.h"
#include "BPlayerHPWidget.h"
#include "BUpgradeWidget.h"
#include "BStatWidget.h"
#include "BBossSpawner.h"
#include "BWantedWidget.h"
#include "Engine/public/EngineUtils.h"

void UBHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameStateBase->OnCountDownStart.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Visible);
	});

	BGameStateBase->OnCountDownDone.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Hidden);
	});

	UWidgetBlueprintGeneratedClass* WidgetAni = Cast<UWidgetBlueprintGeneratedClass>(GetClass());

	for (UWidgetAnimation* Ani : WidgetAni->Animations)
	{
		if (TEXT("ReadyToBossAnim_INST") == Ani->GetName())
		{
			WantedAnimation = Ani;
		}
	}

	ABBossSpawner* BossSpawner;
	for (const auto& entity : FActorRange(GetWorld()))
	{
		BossSpawner = Cast<ABBossSpawner>(entity);
		if (BossSpawner != nullptr)
		{
			BLOG(Warning, TEXT("Find BossSpawner"));
			break;
		}
	}

	BGameStateBase->OnReadyToBoss.AddLambda([this, BossSpawner]() -> void {
		int32 BossIndex = BGameStateBase->GetCurrentWave() / 10;
		WantedWidget->Init(BossSpawner->GetBosses()[BossIndex]);
		PlayWantedAnimation();
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

void UBHUDWidget::PlayWantedAnimation()
{
	PlayAnimation(WantedAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}
