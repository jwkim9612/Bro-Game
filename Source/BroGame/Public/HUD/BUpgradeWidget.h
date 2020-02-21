// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BUpgradeWidget.generated.h"

USTRUCT()
struct FBUpgradeInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Info")
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	EStat Stat;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	int32 IncreaseStat;

	UPROPERTY(EditDefaultsOnly, Category = "Info")
	int32 IncreasePrice;
};

/**
 * 
 */
UCLASS()
class BROGAME_API UBUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init();

private:
	UPROPERTY(EditAnywhere, Category = "Info")
	TArray<struct FBUpgradeInfo> BUpgradeInfo;

	UPROPERTY()
	TArray<class UBUpgradeSlot*> BUpgrades;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* TestVerticalBox;
};
