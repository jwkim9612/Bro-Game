// Fill out your copyright notice in the Description page of Project Settings.


#include "BUpgradeWidget.h"
#include "BUpgradeSlot.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetTree.h"

void UBUpgradeWidget::Init()
{
	BUpgrades.Init(nullptr, BUpgradeInfo.Num());

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	int count = 0;
	UBUpgradeSlot* UpgradeSlot = nullptr;
	for (auto& Widget : Widgets)
	{
		UpgradeSlot = Cast<UBUpgradeSlot>(Widget);

		if (!UpgradeSlot || count >= BUpgradeInfo.Num()) continue;
		UpgradeSlot->InitData(BUpgradeInfo[count]);
		BUpgrades[count] = UpgradeSlot;
		++count;
	}

	for (auto& BUpgrade : BUpgrades)
	{
		BUpgrade->SetVisibility(ESlateVisibility::Visible);
		TestVerticalBox->AddChildToVerticalBox(BUpgrade);
	}
}