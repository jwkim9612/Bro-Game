// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/PlayerController.h"
#include "BUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	TSubclassOf<UUserWidget> GetSelectModeWidgetClass() const;
	TSubclassOf<UUserWidget> GetMainMenuWidgetClass() const;
	TSubclassOf<UUserWidget> GetSelectCharacterWidgetClass() const;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> SelectModeWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> SelectCharacterWidgetClass;

private:
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
