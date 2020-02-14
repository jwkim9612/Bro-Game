// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	void UpdateTimerWidget();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Timer;

	class ABGameModeBase* BGameModeBase = nullptr;

	int32 Min = 0;
	int32 Sec = 0;
};
