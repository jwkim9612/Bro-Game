// Fill out your copyright notice in the Description page of Project Settings.


#include "BSelectCharacter.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"

void UBSelectCharacter::NativeConstruct()
{
	if (BackButton != nullptr)
	{
		BackButton->OnClicked.AddDynamic(this, &UBSelectCharacter::OnBackClicked);
	}
}

void UBSelectCharacter::OnBackClicked()
{
	ABUIPlayerController* BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetSelectModeWidgetClass());
	}
}
