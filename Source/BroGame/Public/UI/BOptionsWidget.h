// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BBaseWidget.h"
#include "BOptionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBOptionsWidget : public UBBaseWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnLanguageClicked();

	UFUNCTION()
	void OnBackClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* LanguageButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
};
