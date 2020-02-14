// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BBaseWidget.h"
#include "BSelectCharacter.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class BROGAME_API UBSelectCharacter : public UBBaseWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnBackClicked();

private:
	UPROPERTY(config)
	TArray<FStringClassReference> Characters;

	UPROPERTY()
	TArray<class UBSelectCharacterButton*> Buttons;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* GridPanel;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditDefaultsOnly ,BlueprintReadWrite, meta = (AllowPrivateAccess = true, UIMin = 0, UIMax = 7))
	int32 MaxCharacterIndex = 0;
};
