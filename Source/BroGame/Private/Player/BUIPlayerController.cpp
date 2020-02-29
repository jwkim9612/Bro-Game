// Fill out your copyright notice in the Description page of Project Settings.


#include "BUIPlayerController.h"
#include "BMainMenuWidget.h"
#include "Blueprint/UserWidget.h"

void ABUIPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

void ABUIPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

	ChangeMenuWidget(MainMenuWidgetClass);

	BCHECK(MainMenuWidgetClass != nullptr);
	BCHECK(SelectModeWidgetClass != nullptr);
	BCHECK(SelectCharacterWidgetClass != nullptr);
	BCHECK(OptionsWidgetClass != nullptr);
	BCHECK(Option_LanguageClass != nullptr);
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

TSubclassOf<UUserWidget> ABUIPlayerController::GetMainMenuWidgetClass() const
{
	return MainMenuWidgetClass;
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetSelectModeWidgetClass() const
{
	return SelectModeWidgetClass;
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetSelectCharacterWidgetClass() const
{
	return SelectCharacterWidgetClass;
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetOptionsWidgetClass() const
{
	return OptionsWidgetClass;
}

TSubclassOf<UUserWidget> ABUIPlayerController::GetOption_LanguageWidgetClass() const
{
	return Option_LanguageClass;
}
