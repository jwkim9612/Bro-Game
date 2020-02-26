// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BWantedWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBWantedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(TSubclassOf<class ABBoss> BossClass);

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* BossImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BossName;
};
