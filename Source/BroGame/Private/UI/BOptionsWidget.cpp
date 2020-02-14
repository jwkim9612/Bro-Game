// Fill out your copyright notice in the Description page of Project Settings.


#include "BOptionsWidget.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"

void UBOptionsWidget::NativeConstruct()
{
	BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());

	if (LanguageButton != nullptr)
	{
		LanguageButton->OnClicked.AddDynamic(this, &UBOptionsWidget::OnLanguageClicked);
	}

	if (BackButton != nullptr)
	{
		BackButton->OnClicked.AddDynamic(this, &UBOptionsWidget::OnBackClicked);
	}
}

void UBOptionsWidget::OnLanguageClicked()
{
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetOption_LanguageWidgetClass());
	}
}

void UBOptionsWidget::OnBackClicked()
{
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetMainMenuWidgetClass());
	}
}