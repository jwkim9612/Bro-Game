// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBPlayerHPWidget::SetHPBarPercent(float HPRatio)
{
	HPBar->SetPercent(HPRatio);
}

void UBPlayerHPWidget::SetHPText(FText InText)
{
	HPText->SetText(InText);
}
