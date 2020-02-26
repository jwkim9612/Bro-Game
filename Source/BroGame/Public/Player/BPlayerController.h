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

private:
	void OnGamePuase();

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
