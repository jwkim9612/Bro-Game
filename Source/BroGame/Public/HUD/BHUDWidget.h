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
	void UpdateHPWidget();
	void PlayWantedAnimation();
	void PlayShowBonusAnimation();
	void PlayHideBonusAnimation();
	void PauseAllAnimation();
	void ResumeAllAnimation();
	void ResumeAnimation(TPair<class UWidgetAnimation*, float> Animation);

	// 스텟과 업그레이드 버튼 클릭관련
	void SetCanNotClickButton();
	void SetCanClickButton();

private:

private:
	TWeakObjectPtr<class ABPlayerState> CurrentPlayerState;

	UPROPERTY(meta = (BindWidget))
	class UBTimerWidget* TimerWidget;

	UPROPERTY(meta = (BindWidget))
	class UBWaveWidget* WaveWidget;

	UPROPERTY(meta = (BindWidget))
	class UBPlayerHPWidget* HPBarWidget;

	UPROPERTY(meta = (BindWidget))
	class UBUpgradeWidget* UpgradeWidget;

	UPROPERTY(meta = (BindWidget))
	class UBStatWidget* StatWidget;

	UPROPERTY(meta = (BindWidget))
	class UBWantedWidget* WantedWidget;

	UPROPERTY(meta = (BindWidget))
	class UBBonusWidget* BonusWidget;

	UPROPERTY()
	class UWidgetAnimation* WantedAnimation;

	UPROPERTY()
	class UWidgetAnimation* ShowBonusAnimation;

	UPROPERTY()
	class UWidgetAnimation* HideBonusAnimation;

	// 애니메이션과 시간
	UPROPERTY()
	TMap<class UWidgetAnimation*, float> Animations;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY()
	class ABPlayerController* BPlayerController;

	FTimerHandle BonusTimerHandle;
	float BonusTimer = 1.0f;
};
