// Fill out your copyright notice in the Description page of Project Settings.


#include "BWantedWidget.h"
#include "BBoss.h"
#include "BBossSpawner.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBWantedWidget::Init(class ABBoss* BBoss)
{
	BCHECK(BBoss != nullptr);

	BossImage->SetBrushFromTexture(BBoss->GetWantedPhoto());
	BossName->SetText(FText::FromName(BBoss->GetBossName()));
}