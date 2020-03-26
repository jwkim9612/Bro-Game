// Fill out your copyright notice in the Description page of Project Settings.


#include "BWindowBase.h"
#include "BInterfaceWidgetBase.h"

void UBWindowBase::Init(class UBInterfaceWidgetBase* InterfaceWidget)
{

}

void UBWindowBase::OnCloseButtonClicked()
{
	BInterfaceWidget->OnInterface();
}
