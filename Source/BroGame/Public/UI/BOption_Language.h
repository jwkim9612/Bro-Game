// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BBaseWidget.h"
#include "BOption_Language.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBOption_Language : public UBBaseWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnEnglishClicked();

	UFUNCTION()
	void OnKoreanClicked();

	UFUNCTION()
	void OnBackClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* EnglishButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* KoreanButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
};
