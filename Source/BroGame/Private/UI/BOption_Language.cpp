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
	// 두 번째 인자는 참이면, 새로운 설정을 사용자의 "GameUserSettings"설정에 저장하여 다시로드 한 후에도 유지함.
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
