// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BInterfaceWidgetBase.h"
#include "BUpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBUpgradeWidget : public UBInterfaceWidgetBase
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
//
//public:
//	void Init();
//	void ShowUpgrade();
//	void HideUpgrade();

private:
	//UPROPERTY(meta = (BindWidget))
	//class UBUpgradeWindow* UpgradeWindow;	

	//UPROPERTY(meta = (BindWidget))
	//class UBWindowBase* Window;	

	//UPROPERTY(meta = (BindWidget))
	//class UBShowButton* ShowButton;

	//UPROPERTY(EditDefaultsOnly, Category = "UI")
	//class UTexture2D* MenuImage;

	//UPROPERTY()
	//class UWidgetAnimation* ShowAnimation;
};
