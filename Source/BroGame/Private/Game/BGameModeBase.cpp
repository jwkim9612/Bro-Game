// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameModeBase.h"
#include "BSaveGame.h"
#include "BPlayer.h"
#include "Blueprint/UserWidget.h"

void ABGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UBSaveGame* BSaveGame = Cast<UBSaveGame>(UGameplayStatics::CreateSaveGameObject(UBSaveGame::StaticClass()));
	if (BSaveGame != nullptr)
	{
		BSaveGame->SaveSlotName = TEXT("Player0");
		BSaveGame->SaveIndex = 0;

		BSaveGame = Cast<UBSaveGame>(UGameplayStatics::LoadGameFromSlot(BSaveGame->SaveSlotName, BSaveGame->SaveIndex));
	}
	
	DefaultPawnClass = BSaveGame->BPlayerClass;
}

void ABGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

}

void ABGameModeBase::StartPlay()
{
	Super::StartPlay();

}

int32 ABGameModeBase::GetDefaultTimeMin() const
{
	return DefaultTimeMin;
}

int32 ABGameModeBase::GetDefaultTimeSec() const
{
	return DefaultTimeSec;
}
