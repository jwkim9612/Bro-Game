// Fill out your copyright notice in the Description page of Project Settings.


#include "BSelectModeWidget.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"

void UBSelectModeWidget::NativeConstruct()
{	
	BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());

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
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetSelectCharacterWidgetClass());
	}
}

void UBSelectModeWidget::OnDuoClicked()
{
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetSelectCharacterWidgetClass());
	}
}

void UBSelectModeWidget::OnBackClicked()
{
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetMainMenuWidgetClass());
	}
}
