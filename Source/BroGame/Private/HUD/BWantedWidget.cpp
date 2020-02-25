// Fill out your copyright notice in the Description page of Project Settings.


#include "BWantedWidget.h"
#include "BBoss.h"
#include "BBossSpawner.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UBWantedWidget::Init(FBBossInfo BossInfo)
{
	ABBoss* Boss = BossInfo.BossClass->GetDefaultObject<ABBoss>();
	BCHECK(Boss != nullptr);

	BossImage->SetBrushFromTexture(Boss->GetWantedPhoto());
	BossName->SetText(FText::FromName(Boss->GetBossName()));
}