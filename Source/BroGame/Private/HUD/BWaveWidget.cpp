// Fill out your copyright notice in the Description page of Project Settings.


#include "BWaveWidget.h"
#include "BGameStateBase.h"
#include "Components/TextBlock.h"

void UBWaveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	BGameStateBase->OnCountDownDone.AddUObject(this, &UBWaveWidget::Update);
	Update();
}

void UBWaveWidget::Update()
{
	BCHECK(BGameStateBase != nullptr);
	CurrentWave = BGameStateBase->GetCurrentWave();

	FText TextWave = FText::FromString(FString::Printf(TEXT("Wave : %d"), CurrentWave));

	Wave->SetText(TextWave);
}
