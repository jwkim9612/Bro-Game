// Fill out your copyright notice in the Description page of Project Settings.


#include "BHUDWidget.h"
#include "BGameModeBase.h"
#include "BTimerWidget.h"

void UBHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ABGameModeBase* BGameMode = Cast<ABGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	BGameMode->OnCountDownStart.AddLambda([this]() -> void {
		TimerWidget->SetVisibility(ESlateVisibility::Visible);
	});

	BGameMode->OnCountDownDone.AddLambda([this]() -> void {
		
		TimerWidget->SetVisibility(ESlateVisibility::Hidden);
	});
}