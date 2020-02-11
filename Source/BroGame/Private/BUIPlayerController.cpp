// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIPlayerController.h"
#include "BMainMenuWidget.h"
#include "Blueprint/UserWidget.h"

void ABUIPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

	ChangeMenuWidget(MainMenuWidgetClass);

	//if (MainMenuWidgetClass != nullptr)
	//{
	//	MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
	//	if (MainMenuWidget != nullptr)
	//	{
	//		MainMenuWidget->AddToViewport();
	//	}
	//}
}

void ABUIPlayerController::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(this, NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetSelectModeWidgetClass() const
{
	return SelectModeWidgetClass;
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetMainMenuWidgetClass() const
{
	return MainMenuWidgetClass;
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetSelectCharacterWidgetClass() const
{
	return SelectCharacterWidgetClass;
}
