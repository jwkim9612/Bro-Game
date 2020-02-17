// Fill out your copyright notice in the Description page of Project Settings.


#include "BTimerWidget.h"
#include "BGameStateBase.h"
#include "Components/TextBlock.h"

void UBTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameStateBase->OnCountDown.AddUObject(this, &UBTimerWidget::UpdateTimerWidget);
	UpdateTimerWidget();
}

void UBTimerWidget::UpdateTimerWidget()
{
	Min = BGameStateBase->GetCurrentTimeMin();
	Sec = BGameStateBase->GetCurrentTimeSec();

	FString str = FString::Printf(TEXT("%02d:%02d"), Min, Sec);

	Timer->SetText(FText::FromString(str));
}
