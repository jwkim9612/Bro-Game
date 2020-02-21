// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BMonsterHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBMonsterHPWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:
	TWeakObjectPtr<class UBMonsterStatComponent> CurrentMonsterState;

public:
	void BindMonsterState(class UBMonsterStatComponent* MonsterStatComponent);
	void UpdateHPWidget();

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;
};