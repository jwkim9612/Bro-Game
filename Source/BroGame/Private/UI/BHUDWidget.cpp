// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUDWidget.h"
#include "BGameStateBase.h"
#include "BTimerWidget.h"

void UBHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABGameStateBase* BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameStateBase->OnCountDownStart.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Visible);
	});

	BGameStateBase->OnCountDownDone.AddLambda([this]() -> void {
		
		TimerWidget->SetVisibility(ESlateVisibility::Hidden);
	});
}