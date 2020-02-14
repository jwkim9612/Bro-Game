// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/SaveGame.h"
#include "BSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UBSaveGame();

public:
	UPROPERTY()
	TSubclassOf<class ABPlayer> BPlayerClass;

	UPROPERTY()
	FString SaveSlotName;

	UPROPERTY()
	int32 SaveIndex;
};
