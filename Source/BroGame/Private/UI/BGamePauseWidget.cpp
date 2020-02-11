// Fill out your copyright notice in the Description page of Project Settings.


#include "BGamePauseWidget.h"
#include "BPlayerController.h"
#include "Components/Button.h"
#include "..\..\Public\UI\BGamePauseWidget.h"

void UBGamePauseWidget::NativeConstruct()
{
	if (ContinueButton != nullptr)
	{
		ContinueButton->OnClicked.AddDynamic(this, &UBGamePauseWidget::OnContinueClicked);
	}

	if (MainMenuButton != nullptr)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UBGamePauseWidget::OnMainMenuClicked);
	}

	if (QuitButton != nullptr)
	{
		QuitButton->OnClicked.AddDynamic(this, &UBGamePauseWidget::OnQuitClicked);
	}
}

void UBGamePauseWidget::OnContinueClicked()
{
	ABPlayerController* BPlayerController = Cast<ABPlayerController>(GetOwningPlayer());
	if (BPlayerController != nullptr)
	{
		RemoveFromParent();
		BPlayerController->ChangeInputMode(true);
		BPlayerController->SetPause(false);
	}
}

void UBGamePauseWidget::OnMainMenuClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}

void UBGamePauseWidget::OnQuitClicked()
{
	BLOG(Warning, TEXT("Quit"));
	//FGenericPlatformMisc::RequestExit(true);
}
