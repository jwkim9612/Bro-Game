// Fill out your copyright notice in the Description page of Project Settings.


#include "BTimerWidget.h"
#include "BGameStateBase.h"
#include "Components/TextBlock.h"

void UBTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameStateBase->OnCountDown.AddUObject(this, &UBTimerWidget::Update);

	Update();
}

void UBTimerWidget::Update()
{
	BCHECK(BGameStateBase != nullptr);
	Min = BGameStateBase->GetCurrentTimeMin();
	Sec = BGameStateBase->GetCurrentTimeSec();

	FText Text = FText::FromString(FString::Printf(TEXT("%02d:%02d"), Min, Sec));

	TimerText->SetText(Text);
}
