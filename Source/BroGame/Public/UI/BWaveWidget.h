// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BWaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBWaveWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	void Update();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Wave;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase = nullptr;

	int32 CurrentWave = 0;
};
