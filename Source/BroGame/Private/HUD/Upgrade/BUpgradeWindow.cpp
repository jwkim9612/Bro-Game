// Fill out your copyright notice in the Description page of Project Settings.


#include "BUpgradeWindow.h"
#include "BUpgradeSlot.h"
#include "BUpgradeWidget.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Blueprint/WidgetTree.h"

void UBUpgradeWindow::Init(class UBInterfaceWidgetBase* InterfaceWidget)
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

	UVerticalBoxSlot* VerticalBoxSlot;
	for (auto& BUpgrade : BUpgrades)
	{
		BUpgrade->SetVisibility(ESlateVisibility::Visible);
		VerticalBoxSlot = VerticalBox->AddChildToVerticalBox(BUpgrade);
	}

	BInterfaceWidget = InterfaceWidget;

	if (CloseButton != nullptr)
	{
		CloseButton->OnClicked.AddDynamic(this, &UBUpgradeWindow::OnCloseButtonClicked);
	}
}
