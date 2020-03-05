// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BBonusWidget.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBBonusWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//virtual void NativeConstruct() override;

public:
	void Init(class UBHUDWidget* HUDWidget);
	void SlotsUpdate();
	void SlotsUpdateOnBossWave();

private:
	UPROPERTY(meta = (BindWidget))
	TArray<class UBBonusSlot*> Bonuses;

	UPROPERTY(EditDefaultsOnly, Category = "Rarelity")
	TArray<EBonusRarelity> UpdateRarelities;
};
