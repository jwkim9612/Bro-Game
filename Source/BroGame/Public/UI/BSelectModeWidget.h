// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BSelectModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBSelectModeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnSingleClicked();

	UFUNCTION()
	void OnDuoClicked();

	UFUNCTION()
	void OnBackClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* SingleButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* DuoButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
};
