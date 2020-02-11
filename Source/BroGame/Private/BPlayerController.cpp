// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerController.h"
#include "BGamePauseWidget.h"
#include "Blueprint/UserWidget.h"

void ABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
}

void ABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ABPlayerController::OnGamePuase);
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
