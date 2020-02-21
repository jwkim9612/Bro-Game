// Fill out your copyright notice in the Description page of Project Settings.


#include "BInterfaceWidgetBase.h"
#include "BWindowBase.h"
#include "BShowButton.h"

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
}

void UBInterfaceWidgetBase::Init()
{
	Window->Init(this);

	BCHECK(MenuImage != nullptr);
	ShowButton->Init(MenuImage, this);
}

void UBInterfaceWidgetBase::ShowInterface()
{
	PlayAnimation(InterfaceAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void UBInterfaceWidgetBase::HideInterface()
{
	PlayAnimation(InterfaceAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
}
