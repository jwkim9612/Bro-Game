// Fill out your copyright notice in the Description page of Project Settings.


#include "BSelectCharacterButton.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "BPlayer.h"

void UBSelectCharacterButton::NativeConstruct()
{



}

void UBSelectCharacterButton::Init(TSubclassOf<class ABPlayer> NewPlayerClass)
{
	if (NewPlayerClass != nullptr)
	{
		Player = NewPlayerClass->GetDefaultObject<ABPlayer>();
		Image->SetBrushFromTexture(Player->GetTexture());
		Name->SetText(FText::FromName(Player->GetName()));
	}

	if (Button != nullptr)
	{
		Button->OnClicked.AddDynamic(this, &UBSelectCharacterButton::OnImageButtonClicked);
	}

	
}

void UBSelectCharacterButton::OnImageButtonClicked()
{
	TSubclassOf<ABPlayer> characterclass = Player->StaticClass();
	if (characterclass != nullptr)
	{
		BLOG(Warning, TEXT(" good"));
	}
	UGameplayStatics::GetGameMode(GetWorld())->DefaultPawnClass = characterclass;
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("test1"), true);
	ABPlayer* character = GetWorld()->SpawnActor<ABPlayer>(Player->StaticClass(), FVector(-500.0f, 400.0f, 230.0f), FRotator(0.0f, 0.0f, 0.0f));

	BLOG(Warning, TEXT("Clicked"));
}
