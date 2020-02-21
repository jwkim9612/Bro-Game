// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BUpgradeSlot.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBUpgradeSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void InitData(struct FBUpgradeInfo& UpgradeInfo);

private:
	UFUNCTION()
	void OnUpgradeButtonClicked();
	void ChangeStat();

	void SetIncreaseStatText(int32 Stat);
	void SetPriceText(int32 Price);
	void SetLevelText(int32 Level);

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* UpgradeButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* UpgradeImage;

	UPROPERTY(meta =(BindWidget))
	class UTextBlock* LevelText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* IncreaseStatText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PriceText;

	UPROPERTY()
	class ABPlayerState* BPlayerState;

	EStat CurrentStat;

	int32 IncreaseStat;
	int32 IncreasePrice;
	int32 CurrentPrice;
	int32 CurrentLevel;
};
