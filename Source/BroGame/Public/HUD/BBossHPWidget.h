// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BBossHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBBossHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetBossImage(UTexture2D* BossTexture);
	void SetBossHP(float HPRatio);
	
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* BossImage;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* BossHP;
};
