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
	// bGameMode = true is FInputModeGameOnly and ShowMouseCursor
	// bGameMode = false is FInputModeUIOnly and NotShowMouseCursor
	void ChangeInputMode(bool bGameMode = true);
	class UBHUDWidget* GetHUDWidget() const;
	void MonsterKill(class ABMonster* KilledMonster);

private:
	void OnGamePuase();
	//void OnClear();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> GamePauseWidgetClass;

private:
	UPROPERTY()
	class UBGamePauseWidget* GamePauseWidget;

	UPROPERTY()
	class UBHUDWidget* BHUDWidget;

	UPROPERTY()
	class ABPlayerState* BPlayerState;
};
