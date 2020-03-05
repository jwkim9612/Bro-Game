// Fill out your copyright notice in the Description page of Project Settings.


#include "BBossHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UBBossHPWidget::SetBossImage(UTexture2D* BossTexture)
{
	BCHECK(BossTexture != nullptr);
	BossImage->SetBrushFromTexture(BossTexture);
}

void UBBossHPWidget::SetBossHP(float HPRatio)
{
	BossHP->SetPercent(HPRatio);
}
