// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void BindPlayerState(class ABPlayerState* PlayerState);
	void BindBossHPWidget(class ABBoss* BBoss);
	void UpdatePlayerHPWidget();
	void UpdateBossHPWidget();
	void PlayWantedAnimation();
	void PlayShowBonusAnimation();
	void PlayHideBonusAnimation();
	void PauseAllAnimation();
	void ResumeAllAnimation();
	void ResumeAnimation(TPair<class UWidgetAnimation*, float> Animation);
	
	class UBUpgradeWidget* GetUpgradeWidget() const;
	class UBStatWidget* GetStatWidget() const;

	bool IsOpendedInterface() const;
	void AddCountOfOpenedInterface();
	void MinCountOfOpenedInterface();

	// 스텟과 업그레이드 버튼 클릭관련
	void SetCanNotClickButton();
	void SetCanClickButton();

	void OnCinemaEnded();

public:

private:

private:
	TWeakObjectPtr<class ABPlayerState> CurrentPlayerState;
	TWeakObjectPtr<class UBEnemyStatComponent> CurrentBossStat;

	UPROPERTY(meta = (BindWidget))
	class UBTimerWidget* TimerWidget;

	UPROPERTY(meta = (BindWidget))
	class UBWaveWidget* WaveWidget;

	UPROPERTY(meta = (BindWidget))
	class UBPlayerHPWidget* PlayerHPBarWidget;

	UPROPERTY(meta = (BindWidget))
	class UBUpgradeWidget* UpgradeWidget;

	UPROPERTY(meta = (BindWidget))
	class UBStatWidget* StatWidget;

	UPROPERTY(meta = (BindWidget))
	class UBWantedWidget* WantedWidget;

	UPROPERTY(meta = (BindWidget))
	class UBBonusWidget* BonusWidget;

	UPROPERTY(meta = (BindWidget))
	class UBBossHPWidget* BossHPWidget;

	UPROPERTY()
	class UWidgetAnimation* WantedAnimation;

	UPROPERTY()
	class UWidgetAnimation* ShowBonusAnimation;

	UPROPERTY()
	class UWidgetAnimation* HideBonusAnimation;

	// 인터페이스 열려있는지.
	int32 CountOfOpenedInterface;

	// 애니메이션과 시간
	UPROPERTY()
	TMap<class UWidgetAnimation*, float> Animations;

	UPROPERTY()
	class UBGameInstance* BGameInstance;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY()
	class ABPlayerController* BPlayerController;

	FTimerHandle BonusTimerHandle;
	float BonusTimer = 3.0f;

	// 시네마틱
	UPROPERTY()
	class ABLevelScriptActor* BLevelScriptActor;

	FTimerHandle SequenceTimerHandle;
	float SequenceTimer = 1.0f;
};
