// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BMoneyWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBMoneyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	void Update();

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MoneyText;

	int32 Money = 0;

	UPROPERTY()
	class ABPlayerState* BPlayerState;
};
