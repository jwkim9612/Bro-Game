// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BPlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHPBarPercent(float HPRatio);
	void SetHPText(FText InText);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HPText;
};
