// Fill out your copyright notice in the Description page of Project Settings.


#include "BStatWindow.h"
#include "BInterfaceWidgetBase.h"
#include "BStatSlot.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Blueprint/WidgetTree.h"
#include "..\..\..\Public\HUD\Stat\BStatWindow.h"

void UBStatWindow::Init(class UBInterfaceWidgetBase* InterfaceWidget)
{
	BStats.Init(nullptr, BStatInfo.Num());

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	int count = 0;
	UBStatSlot* StatSlot = nullptr;
	for (auto& Widget : Widgets)
	{
		StatSlot = Cast<UBStatSlot>(Widget);

		if (!StatSlot || count >= BStatInfo.Num()) continue;
		StatSlot->InitData(BStatInfo[count]);
		BStats[count] = StatSlot;
		++count;
	}

	UVerticalBoxSlot* VerticalBoxSlot;
	for (auto& BStat : BStats)
	{
		BStat->SetVisibility(ESlateVisibility::Visible);
		VerticalBoxSlot = VerticalBox->AddChildToVerticalBox(BStat);
	}

	BInterfaceWidget = InterfaceWidget;

	if (CloseButton != nullptr)
	{
		CloseButton->OnClicked.AddDynamic(this, &UBStatWindow::OnCloseButtonClicked);
	}
}

void UBStatWindow::OnCloseButtonClicked()
{
	BInterfaceWidget->HideInterface();
}
