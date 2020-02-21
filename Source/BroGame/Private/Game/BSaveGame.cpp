// Fill out your copyright notice in the Description page of Project Settings.


#include "BSaveGame.h"

UBSaveGame::UBSaveGame()
{
	BPlayerClass = nullptr;
	SaveSlotName = TEXT("Player0");
	SaveIndex = 0;
}