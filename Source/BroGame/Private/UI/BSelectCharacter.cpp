// Fill out your copyright notice in the Description page of Project Settings.


#include "BSelectCharacter.h"
#include "BUIPlayerController.h"
#include "BSelectCharacterButton.h"
#include "BPlayer.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/AssetManager.h"

void UBSelectCharacter::NativeConstruct()
{
	BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());

	if (BackButton != nullptr)
	{
		BackButton->OnClicked.AddDynamic(this, &UBSelectCharacter::OnBackClicked);
	}

	Buttons.Init(nullptr, MaxCharacterIndex + 1);

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);

	int CharacterNum = 0;
	UBSelectCharacterButton* Button = nullptr;
	for (auto& widget : widgets)
	{
		Button = Cast<UBSelectCharacterButton>(widget);

		if (!Button || CharacterNum > MaxCharacterIndex) continue;
		TSubclassOf<ABPlayer> NewCharacter = Characters[CharacterNum].TryLoadClass<ABPlayer>();
		Button->Init(NewCharacter);
		Buttons[CharacterNum] = Button;
		++CharacterNum;
	}

	UUniformGridSlot* GridSlot;
	BCHECK(MaxCharacterIndex <= 7);

	for (int i = 0; i <= MaxCharacterIndex; ++i)
	{
		Buttons[i]->SetVisibility(ESlateVisibility::Visible);
		if (i < 4)
		{
			GridSlot = GridPanel->AddChildToUniformGrid(Buttons[i], 0, i);
		}
		else
		{
			GridSlot = GridPanel->AddChildToUniformGrid(Buttons[i], 1, i - 4);
		}
		GridSlot->SetHorizontalAlignment(HAlign_Center);
		GridSlot->SetVerticalAlignment(VAlign_Center);
	}
}

void UBSelectCharacter::OnBackClicked()
{
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetSelectModeWidgetClass());
	}
}
