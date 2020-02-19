// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Blueprint/UserWidget.h"
#include "BSelectCharacterButton.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBSelectCharacterButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void Init(TSubclassOf<class ABPlayer> NewPlayerClass);

private:
	UFUNCTION()
	void OnImageButtonClicked();

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABPlayer> PlayerClass;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
};
