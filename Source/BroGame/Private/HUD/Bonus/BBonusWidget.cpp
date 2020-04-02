// Fill out your copyright notice in the Description page of Project Settings.


#include "BBonusWidget.h"
#include "BBonusSlot.h"
#include "BGameStateBase.h"
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
		Bonuses[SlotNum]->OnBonusClicked.AddLambda([this]() -> void {
			// 여러번 클릭해서 버그를 사용하지 않기위해.
			SetVisibility(ESlateVisibility::HitTestInvisible);
		});

		++SlotNum;;
	}
}

void UBBonusWidget::SlotsUpdate()
{
	SetVisibility(ESlateVisibility::Visible);

	for (auto& Bonus : Bonuses)
	{
		Bonus->RandomUpdate();
	}
}

void UBBonusWidget::SlotsUpdateOnBossWave()
{
	SetVisibility(ESlateVisibility::Visible);

	ABGameStateBase* BGameState = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	// 인덱스는 0부터 시작이기때문에 1을 뺌
	int32 BossIndex = BGameState->GetCurrentWave() / 5 - 1;

	for (auto& Bonus : Bonuses)
	{
		Bonus->RandomUpdateByRarelity(UpdateRarelities[BossIndex]);
	}
}


