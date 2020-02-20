// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerController.h"
#include "BGamePauseWidget.h"
#include "BGameStateBase.h"
#include "BPlayer.h"
#include "BSaveGame.h"
#include "BPlayerState.h"
#include "BHUDWidget.h"
#include "BMonster.h"
#include "BMonsterStatComponent.h"
#include "Blueprint/UserWidget.h"

void ABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());

	if (HUDWidgetClass != nullptr)
	{
		BHUDWidget = CreateWidget<UBHUDWidget>(this, HUDWidgetClass);
		if (BHUDWidget != nullptr)
		{
			BHUDWidget->AddToViewport();
		}
	}
	
	BPlayerState = Cast<ABPlayerState>(PlayerState);
	BCHECK(BPlayerState);
	BHUDWidget->BindPlayerState(BPlayerState);
}

void ABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ABPlayerController::OnGamePuase);
	InputComponent->BindAction(TEXT("Clear"), EInputEvent::IE_Pressed, this, &ABPlayerController::OnClear);
}

void ABPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	
}

void ABPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

UBHUDWidget * ABPlayerController::GetHUDWidget() const
{
	return BHUDWidget;
}

void ABPlayerController::MonsterKill(ABMonster * KilledMonster)
{
	BPlayerState->AddMoney(KilledMonster->GetCurrentStat()->GetDropMoney());
}


void ABPlayerController::OnGamePuase()
{
	GamePauseWidget = CreateWidget<UBGamePauseWidget>(this, GamePauseWidgetClass);
	if (GamePauseWidget != nullptr)
	{
		GamePauseWidget->AddToViewport(3);
	}

	SetPause(true);
	ChangeInputMode(false);
}

void ABPlayerController::OnClear()
{
	ABGameStateBase* BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	if (!(BGameStateBase->IsStageClear()))
	{
		BGameStateBase->SetIsClear(true);
		BGameStateBase->StartTimer();
	}
}
