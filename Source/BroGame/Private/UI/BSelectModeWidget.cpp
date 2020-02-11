// Fill out your copyright notice in the Description page of Project Settings.


#include "BSelectModeWidget.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"

void UBSelectModeWidget::NativeConstruct()
{	
	if (SingleButton != nullptr)
	{
		SingleButton->OnClicked.AddDynamic(this, &UBSelectModeWidget::OnSingleClicked);
	}

	if (DuoButton != nullptr)
	{
		DuoButton->OnClicked.AddDynamic(this, &UBSelectModeWidget::OnDuoClicked);
	}

	if (BackButton != nullptr)
	{
		BackButton->OnClicked.AddDynamic(this, &UBSelectModeWidget::OnBackClicked);
	}
}

void UBSelectModeWidget::OnSingleClicked()
{
	BLOG(Warning, TEXT("Single"));
}

void UBSelectModeWidget::OnDuoClicked()
{
	BLOG(Warning, TEXT("Duo"));
}

void UBSelectModeWidget::OnBackClicked()
{
	ABUIPlayerController* BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetMainMenuWidgetClass());
	}
}
