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

	UPROPERTY()
	class UWidgetAnimation* WantedAnimation;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;
};
