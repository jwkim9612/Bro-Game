// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BShowButton.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBShowButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(class UTexture2D* Texture, class UBInterfaceWidgetBase* InterfaceWidget);
	
public:
	UFUNCTION()
	void OnShowButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* ShowButton;

	UPROPERTY(meta = (BindWidget))
	class UImage* ShowImage;

	UPROPERTY()
	class UBInterfaceWidgetBase* BInterfaceWidget;
};
