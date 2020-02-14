// Fill out your copyright notice in the Description page of Project Settings.


#include "BOption_Language.h"
#include "BUIPlayerController.h"
#include "Components/Button.h"
#include "Kismet/KismetInternationalizationLibrary.h"

void UBOption_Language::NativeConstruct()
{
	BUIPlayerController = Cast<ABUIPlayerController>(GetOwningPlayer());

	if (EnglishButton != nullptr)
	{
		EnglishButton->OnClicked.AddDynamic(this, &UBOption_Language::OnEnglishClicked);
	}

	if (KoreanButton != nullptr)
	{
		KoreanButton->OnClicked.AddDynamic(this, &UBOption_Language::OnKoreanClicked);
	}

	if (BackButton != nullptr)
	{
		BackButton->OnClicked.AddDynamic(this, &UBOption_Language::OnBackClicked);
	}
}

void UBOption_Language::OnEnglishClicked()
{
	// �� ��° ���ڴ� ���̸�, ���ο� ������ ������� "GameUserSettings"������ �����Ͽ� �ٽ÷ε� �� �Ŀ��� ������.
	UKismetInternationalizationLibrary::SetCurrentLanguage(TEXT("en"), true);
}

void UBOption_Language::OnKoreanClicked()
{
	UKismetInternationalizationLibrary::SetCurrentLanguage(TEXT("ko"), true);
}

void UBOption_Language::OnBackClicked()
{
	if (BUIPlayerController != nullptr)
	{
		BUIPlayerController->ChangeMenuWidget(BUIPlayerController->GetOptionsWidgetClass());
	}
}
