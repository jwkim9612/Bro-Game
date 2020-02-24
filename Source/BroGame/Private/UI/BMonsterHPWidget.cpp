// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterHPWidget.h"
#include "BEnemyStatComponent.h"
#include "Components/ProgressBar.h"

void UBMonsterHPWidget::BindMonsterState(class UBEnemyStatComponent* MonsterStatComponent)
{
	BCHECK(MonsterStatComponent != nullptr);

	CurrentMonsterState = MonsterStatComponent;
	MonsterStatComponent->OnHPChanged.AddUObject(this, &UBMonsterHPWidget::UpdateHPWidget);
}

void UBMonsterHPWidget::UpdateHPWidget()
{
	if (HPBar != nullptr)
	{
		HPBar->SetPercent(CurrentMonsterState->GetHPRatio());
	}
}
