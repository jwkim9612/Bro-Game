// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameOverWidget.h"
#include "Components/Button.h"

void UBGameOverWidget::NativeConstruct()
{
	if (nullptr != RetryButton)
	{
		RetryButton->OnClicked.AddDynamic(this, &UBGameOverWidget::OnRetryClicked);
	}

	if (nullptr != BacktoTitleButton)
	{
		BacktoTitleButton->OnClicked.AddDynamic(this, &UBGameOverWidget::OnBacktoTitleClicked);
	}
}

void UBGameOverWidget::OnRetryClicked()
{
	BLOG(Warning, TEXT("Retry"));
}

void UBGameOverWidget::OnBacktoTitleClicked()
{
	BLOG(Warning, TEXT("Backtotitle"));
}
