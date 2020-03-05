// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BWindowBase.h"
#include "BUpgradeWindow.generated.h"

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
class BROGAME_API UBUpgradeWindow : public UBWindowBase
{
	GENERATED_BODY()
	
public:
	void Init(class UBInterfaceWidgetBase* InterfaceWidget) override;
	
	void OnCloseButtonClicked() override;

private:
	UPROPERTY(EditAnywhere, Category = "Info")
	TArray<struct FBUpgradeInfo> BUpgradeInfo;

	UPROPERTY()
	TArray<class UBUpgradeSlot*> BUpgrades;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* VerticalBox;
};
