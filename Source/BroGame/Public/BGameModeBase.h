// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/GameModeBase.h"
#include "BGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;
};
