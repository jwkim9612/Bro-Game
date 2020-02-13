// Fill out your copyright notice in the Description page of Project Settings.


#include "BOptionsWidget.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"

void UBOptionsWidget::NativeConstruct()
{
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
	ABUIPlayerController* BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetOption_LanguageWidgetClass());
	}
}

void UBOptionsWidget::OnBackClicked()
{
	ABUIPlayerController* BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetMainMenuWidgetClass());
	}
}