// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/PlayerController.h"
#include "BPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;

public:
	class UBHUDWidget* GetHUDWidget() const;
	class UBGamePauseWidget* GetGamePauseWidget() const;
	void MonsterKill(class ABEnemyBase* KilledMonster);

	// false = SetInputMode(FInputModeGameOnly())
	// true = SetInputMode(FInputModeGameAndUI());
	void SetClickMode(bool IsClickMode);

	void OnGameOver();

private:
	void OnGamePuase();
	void OnStatWindow();
	void OnUpgradeWindow();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> GamePauseWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UBGameOverWidget> GameOverWidgetClass;

private:
	UPROPERTY()
	class UBGamePauseWidget* GamePauseWidget;

	UPROPERTY()
	class UBHUDWidget* BHUDWidget;

	UPROPERTY()
	class UBGameOverWidget* GameOverWidget;

	UPROPERTY()
	class ABPlayerState* BPlayerState;

	UPROPERTY()
	class ABPlayer* BPlayer;
};
