// Fill out your copyright notice in the Description page of Project Settings.


#include "BInterfaceWidgetBase.h"
#include "BWindowBase.h"
#include "BShowButton.h"
#include "BPlayerController.h"
#include "BHUDWidget.h"

void UBInterfaceWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	UWidgetBlueprintGeneratedClass* WidgetAni = Cast<UWidgetBlueprintGeneratedClass>(GetClass());

	for (UWidgetAnimation* Ani : WidgetAni->Animations)
	{
		if (TEXT("InterfaceAnim_INST") == Ani->GetName())
		{
			InterfaceAnimation = Ani;
		}
	}

	BPlayerContoller = Cast<ABPlayerController>(GetOwningPlayer());
	BCHECK(nullptr != BPlayerContoller);

	BHUDWidget = Cast<UBHUDWidget>(BPlayerContoller->GetHUDWidget());
	BCHECK(nullptr != BHUDWidget);
}

void UBInterfaceWidgetBase::Init()
{
	Window->Init(this);

	BCHECK(nullptr != MenuImage);
	ShowButton->Init(MenuImage, this, MappingKey);
}

void UBInterfaceWidgetBase::OnInterface()
{
	if (IsOpened())
	{
		HideInterface();
		BHUDWidget->MinCountOfOpenedInterface();
		BPlayerContoller->SetClickMode(false);
	}
	else
	{
		ShowInterface();
		BPlayerContoller->SetClickMode(true);
		BHUDWidget->AddCountOfOpenedInterface();
	}
}

void UBInterfaceWidgetBase::ShowInterface()
{
	PlayAnimation(InterfaceAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	bIsOpened = true;
}

void UBInterfaceWidgetBase::HideInterface()
{
	PlayAnimation(InterfaceAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
	bIsOpened = false;
}

bool UBInterfaceWidgetBase::IsOpened() const
{
	return bIsOpened;
}
