// Fill out your copyright notice in the Description page of Project Settings.


#include "BBonusWidget.h"
#include "BBonusSlot.h"
#include "Blueprint/WidgetTree.h"
#include "..\..\..\Public\HUD\Bonus\BBonusWidget.h"

void UBBonusWidget::Init(UBHUDWidget * HUDWidget)
{
	Bonuses.Init(nullptr, 3);

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	int32 SlotNum = 0;
	UBBonusSlot* BonusSlot = nullptr;
	for (auto& Widget : Widgets)
	{
		BonusSlot = Cast<UBBonusSlot>(Widget);

		if (!BonusSlot) continue;
		BonusSlot->Init(HUDWidget);
		Bonuses[SlotNum] = BonusSlot;
		++SlotNum;;
	}
}

void UBBonusWidget::SlotsUpdate()
{
	for (auto& Bonus : Bonuses)
	{
		Bonus->Update();
	}
}
