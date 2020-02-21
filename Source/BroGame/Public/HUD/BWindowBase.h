// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BWindowBase.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBWindowBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Init(class UBInterfaceWidgetBase* InterfaceWidget);

	UFUNCTION()
	virtual void OnCloseButtonClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY()
	class UBInterfaceWidgetBase* BInterfaceWidget;
};
