// Fill out your copyright notice in the Description page of Project Settings.


#include "BTimerWidget.h"
#include "BGameModeBase.h"
#include "Components/TextBlock.h"

void UBTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BGameModeBase = Cast<ABGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	BGameModeBase->OnCountDown.AddUObject(this, &UBTimerWidget::UpdateTimerWidget);
	UpdateTimerWidget();
}

void UBTimerWidget::UpdateTimerWidget()
{
	Min = BGameModeBase->GetCurrentTimeMin();
	Sec = BGameModeBase->GetCurrentTimeSec();

	FString str = FString::Printf(TEXT("%02d:%02d"), Min, Sec);

	Timer->SetText(FText::FromString(str));
}
