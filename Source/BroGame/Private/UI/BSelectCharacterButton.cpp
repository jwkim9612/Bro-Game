// Fill out your copyright notice in the Description page of Project Settings.


#include "BSelectCharacterButton.h"
#include "BSaveGame.h"
#include "BGameInstance.h"
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
		PlayerClass = NewPlayerClass;
		ABPlayer* Player = NewPlayerClass->GetDefaultObject<ABPlayer>();
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
	UBSaveGame* BSaveGame = Cast<UBSaveGame>(UGameplayStatics::CreateSaveGameObject(UBSaveGame::StaticClass()));
	if (BSaveGame != nullptr)
	{
		BSaveGame->BPlayerClass = PlayerClass;
	}

	UBGameInstance* BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BCHECK(BGameInstance != nullptr);
	BGameInstance->LoadMonster();
	BGameInstance->LoadBoss();

	UGameplayStatics::SaveGameToSlot(BSaveGame, BSaveGame->SaveSlotName, BSaveGame->SaveIndex);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("test1"), true);
}
