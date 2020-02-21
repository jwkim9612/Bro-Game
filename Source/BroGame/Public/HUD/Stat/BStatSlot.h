// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BStatSlot.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBStatSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;

public:
	void InitData(struct FBStatInfo& StatInfo);

private:
	void OnStatChanged();
	void ChangeStatText();

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* StatImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StatText;

	UPROPERTY()
	class ABPlayerState* BPlayerState;

	EStat CurrentStat;

	int32 CurrentAttack = 0;
	int32 CurrentMaxHP = 0;
	int32 CurrentSpeed = 0;
};
