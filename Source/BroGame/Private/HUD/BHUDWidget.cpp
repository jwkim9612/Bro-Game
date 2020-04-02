// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUDWidget.h"
#include "BGameInstance.h"
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
#include "BEnemyStatComponent.h"
#include "BBoss.h"
#include "BBossHPWidget.h"
#include "BLevelScriptActor.h"
#include "LevelSequencePlayer.h"
#include "Engine/public/EngineUtils.h"

void UBHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BPlayerController = Cast<ABPlayerController>(GetOwningPlayer());
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	BCHECK(BPlayerController != nullptr);
	BCHECK(BGameStateBase != nullptr);
	BCHECK(BGameInstance != nullptr);

	BLevelScriptActor = BGameInstance->GetCurrentLevelScriptActor();
	BCHECK(BLevelScriptActor != nullptr);

	BGameStateBase->OnCountDownStart.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Visible);
	});

	BGameStateBase->OnCountDownDone.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Hidden);
	});

	BGameInstance->GetCurrentLevelScriptActor()->OnEndCinematic.AddUObject(this, &UBHUDWidget::OnCinemaEnded);


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

		if (TEXT("GameClearAnim_INST") == Ani->GetName())
		{
			GameClearAnimation = Ani;
			Animations.Add(GameClearAnimation, 0.0f);
		}
	}

	ABBossSpawner* BossSpawner;
	for (TActorIterator<ABBossSpawner> It(GetWorld()); It; ++It)
	{
		BossSpawner = Cast<ABBossSpawner>(*It);
		if (BossSpawner != nullptr)
		{
			BLOG(Warning, TEXT("Find BossSpawner"));
			break;
		}
	}

	BGameStateBase->OnReadyToBoss.AddLambda([this, BossSpawner]() -> void {
		BossSpawner->InitBossData();
		WantedWidget->Init(BossSpawner->GetCurrentBoss());
		PlayWantedAnimation();
	});

	BGameStateBase->OnBonusWaveClear.AddLambda([this]() -> void {
		GetWorld()->GetTimerManager().SetTimer(BonusTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			// 보너스탄 클리어후에 탄이 넘어가기때문에 바로전 웨이브가 Boss였는지 확인해야함.
			if (BGameStateBase->IsBossNextWave())
			{
				BonusWidget->SlotsUpdateOnBossWave();
			}
			else
			{
				BonusWidget->SlotsUpdate();
			}

			BPlayerController->SetClickMode(true);
			PlayShowBonusAnimation();
			BPlayerController->SetPause(true);
		}), BonusTimer, false);
	});

	BGameStateBase->OnIsBossDead.AddLambda([this]() -> void {
		BossHPWidget->SetVisibility(ESlateVisibility::Collapsed);
	});

	BGameStateBase->OnBossCountDownDone.AddLambda([this]() -> void {
		if (BLevelScriptActor->PlayBossCinematic(BGameStateBase->GetCurrentBossWave()))
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
		BossHPWidget->SetVisibility(ESlateVisibility::Visible);
	});

	BGameStateBase->OnGameClear.AddLambda([this]() -> void {
		PlayGameClearAnimation();
		GameClearTimer = GameClearAnimation->GetEndTime();
		GetWorld()->GetTimerManager().SetTimer(GameClearTimerHandle, FTimerDelegate::CreateLambda([this]() -> void {
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"), true);
		}), GameClearTimer, false);
	});

	UpgradeWidget->Init();
	StatWidget->Init();
	BonusWidget->Init(this);
}

void UBHUDWidget::BindPlayerState(ABPlayerState * PlayerState)
{
	BCHECK(PlayerState != nullptr);

	CurrentPlayerState = PlayerState;
	PlayerState->OnHPChanged.AddUObject(this, &UBHUDWidget::UpdatePlayerHPWidget);
	PlayerState->OnMaxHPChanged.AddUObject(this, &UBHUDWidget::UpdatePlayerHPWidget);
}

void UBHUDWidget::BindBossHPWidget(ABBoss * BBoss)
{
	BCHECK(BBoss != nullptr);

	CurrentBossStat = BBoss->GetCurrentStat();
	CurrentBossStat->OnHPChanged.AddUObject(this, &UBHUDWidget::UpdateBossHPWidget);
	BossHPWidget->SetBossHP(1.0f);
	BossHPWidget->SetBossImage(BBoss->GetWantedPhoto());
}

void UBHUDWidget::UpdatePlayerHPWidget()
{
	BCHECK(CurrentPlayerState != nullptr);
	PlayerHPBarWidget->SetHPBarPercent(CurrentPlayerState->GetHPRatio());
	PlayerHPBarWidget->SetHPText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), static_cast<float>(CurrentPlayerState->GetCurrentHP()), static_cast<float>(CurrentPlayerState->GetCurrentMaxHP()))));
}

void UBHUDWidget::UpdateBossHPWidget()
{
	BCHECK(CurrentBossStat != nullptr);
	BossHPWidget->SetBossHP(CurrentBossStat->GetHPRatio());
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

void UBHUDWidget::PlayGameClearAnimation()
{
	PlayAnimation(GameClearAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
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

UBUpgradeWidget * UBHUDWidget::GetUpgradeWidget() const
{
	return UpgradeWidget;
}

UBStatWidget * UBHUDWidget::GetStatWidget() const
{
	return StatWidget;
}

bool UBHUDWidget::IsOpendedInterface() const
{
	return CountOfOpenedInterface > 0 ? true : false;
}

void UBHUDWidget::AddCountOfOpenedInterface()
{
	++CountOfOpenedInterface;
}

void UBHUDWidget::MinCountOfOpenedInterface()
{
	--CountOfOpenedInterface;
}

void UBHUDWidget::SetCanNotClickButton()
{
	StatWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	UpgradeWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UBHUDWidget::SetCanClickButton()
{
	StatWidget->SetVisibility(ESlateVisibility::Visible);
	UpgradeWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBHUDWidget::OnCinemaEnded()
{
	SetVisibility(ESlateVisibility::Visible);
}
