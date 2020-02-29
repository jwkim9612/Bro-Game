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
#include "BBonusWidget.h"
#include "BPlayerController.h"
#include "Engine/public/EngineUtils.h"

void UBHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BPlayerController = Cast<ABPlayerController>(GetOwningPlayer());
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
			Animations.Add(WantedAnimation, 0.0f);
		}

		if (TEXT("ShowBonusAnim_INST") == Ani->GetName())
		{
			ShowBonusAnimation = Ani;
			Animations.Add(ShowBonusAnimation, 0.0f);
		}

		if (TEXT("HideBonusAnim_INST") == Ani->GetName())
		{
			HideBonusAnimation = Ani;
			Animations.Add(HideBonusAnimation, 0.0f);
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
		int32 BossIndex = (BGameStateBase->GetCurrentWave() / 10) - 1;
		WantedWidget->Init(BossSpawner->GetBosses()[BossIndex]);
		PlayWantedAnimation();
	});

	BGameStateBase->OnBonusWaveClear.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().SetTimer(BonusTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			BonusWidget->SlotsUpdate();
			PlayShowBonusAnimation();
			BPlayerController->SetPause(true);
		}), BonusTimer, false);
	});

	UpgradeWidget->Init();
	StatWidget->Init();
	BonusWidget->Init(this);
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

void UBHUDWidget::PlayShowBonusAnimation()
{
	PlayAnimation(ShowBonusAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UBHUDWidget::PlayHideBonusAnimation()
{
	PlayAnimation(HideBonusAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UBHUDWidget::PauseAllAnimation()
{
	for (auto& Animation : Animations)
	{
		if (IsAnimationPlaying(Animation.Key))
		{
			Animation.Value = PauseAnimation(Animation.Key);
		}
	}
}

void UBHUDWidget::ResumeAllAnimation()
{
	for (auto& Animation : Animations)
	{
		if (Animation.Value != 0.0f)
		{
			ResumeAnimation(Animation);
		}
	}
}

void UBHUDWidget::ResumeAnimation(TPair<class UWidgetAnimation*, float> Animation)
{
	PlayAnimation(Animation.Key, Animation.Value, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UBHUDWidget::SetCanNotClickButton()
{
	StatWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	UpgradeWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UBHUDWidget::SetCanClickButton()
{
	StatWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	UpgradeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
