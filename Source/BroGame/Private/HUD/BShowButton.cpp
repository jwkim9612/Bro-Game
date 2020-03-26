// Fill out your copyright notice in the Description page of Project Settings.


#include "BShowButton.h"
#include "BInterfaceWidgetBase.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBShowButton::Init(UTexture2D* Texture, UBInterfaceWidgetBase* InterfaceWidget, FName NewKeyName)
{
	BInterfaceWidget = InterfaceWidget;
	ShowImage->SetBrushFromTexture(Texture);
	MappingKeyText->SetText(FText::FromName(NewKeyName));

	if (ShowButton != nullptr)
	{
		ShowButton->OnClicked.AddDynamic(this, &UBShowButton::OnShowButtonClicked);
	}
}

void UBShowButton::OnShowButtonClicked()
{
	BInterfaceWidget->ShowInterface();
}
