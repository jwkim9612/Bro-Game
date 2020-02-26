// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BInterfaceWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBInterfaceWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

public:
	void Init();
	void ShowInterface();
	void HideInterface();

private:
	UPROPERTY(meta = (BindWidget))
	class UBWindowBase* Window;

	UPROPERTY(meta = (BindWidget))
	class UBShowButton* ShowButton;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	class UTexture2D* MenuImage;

	UPROPERTY()
	class UWidgetAnimation* InterfaceAnimation;
};
