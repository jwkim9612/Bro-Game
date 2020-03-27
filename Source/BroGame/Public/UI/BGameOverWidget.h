// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnRetryClicked();

	UFUNCTION()
	void OnBacktoTitleClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RetryButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BacktoTitleButton;
};
