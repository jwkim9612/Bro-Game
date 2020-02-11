// Fill out your copyright notice in the Description page of Project Settings.


#include "BMainMenuWidget.h"
#include "BGameModeBase.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "..\..\Public\UI\BMainMenuWidget.h"

void UBMainMenuWidget::NativeConstruct()
{
	if (PlayButton != nullptr)
	{
		PlayButton->OnClicked.AddDynamic(this, &UBMainMenuWidget::OnPlayClicked);
	}
	
	if (OptionsButton != nullptr)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UBMainMenuWidget::OnOptionsClicked);
	}
	
	if (QuitButton != nullptr)
	{
		QuitButton->OnClicked.AddDynamic(this, &UBMainMenuWidget::OnQuitClicked);
	}
}

void UBMainMenuWidget::OnPlayClicked()
{
	ABUIPlayerController* BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetSelectModeWidgetClass());
	}

	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("test1"), true);
}

void UBMainMenuWidget::OnOptionsClicked()
{
	BLOG(Warning, TEXT("Options!"));
}

void UBMainMenuWidget::OnQuitClicked()
{
	BLOG(Warning, TEXT("Quit!"));
	//FGenericPlatformMisc::RequestExit(true);
}
