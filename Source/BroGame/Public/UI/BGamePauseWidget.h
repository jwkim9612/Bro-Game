// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BGamePauseWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMainMenuClickedDelegate);

/**
 * 
 */
UCLASS()
class BROGAME_API UBGamePauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	// �Ʒ��� OnMainMenuClicked�� �̸��� ���Ƽ� �Ŀ� �����ؾ���.
	FOnMainMenuClickedDelegate FOnMainMenuClicked;

private:
	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnMainMenuClicked();

	UFUNCTION()
	void OnQuitClicked();
	
private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ContinueButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;
};
