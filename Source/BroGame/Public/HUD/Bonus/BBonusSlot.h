// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BBonusSlot.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnBonusClickedDelegate);

/**
 * 
 */
UCLASS()
class BROGAME_API UBBonusSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void Init(class UBHUDWidget* HUDWidget);
	void RandomUpdate();
	void RandomUpdateByRarelity(EBonusRarelity Rarelity);
	void UpdateBonusText();
	void UpdateBonusImage();
	void UpdateColorByRarelity();
	void UpdateWidget();

public:
	FOnBonusClickedDelegate OnBonusClicked;

private:
	UFUNCTION()
	void OnBonusButtonClicked();
	
private:
	struct FBBonusInfo BonusInfo;

	UPROPERTY(meta = (BindWidget))
	class UBorder* ColorByRarelity;

	UPROPERTY(meta = (BindWidget))
	class UButton* BonusButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* BonusImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BonusText;

	UPROPERTY()
	class UBHUDWidget* BHUDWidget;

	UPROPERTY()
	class UBGameInstance* BGameInstance;

	UPROPERTY()
	class ABPlayerController* BPlayerContoller;

	UPROPERTY()
	class ABPlayerState* BPlayerState;
};
