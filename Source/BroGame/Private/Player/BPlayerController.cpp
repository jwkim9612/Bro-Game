// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerController.h"
#include "BGamePauseWidget.h"
#include "BGameStateBase.h"
#include "BPlayer.h"
#include "BSaveGame.h"
#include "BPlayerState.h"
#include "BHUDWidget.h"
#include "BMonster.h"
#include "BEnemyStatComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/RandomStream.h"

void ABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	if (HUDWidgetClass != nullptr)
	{
		BHUDWidget = CreateWidget<UBHUDWidget>(this, HUDWidgetClass);
		if (BHUDWidget != nullptr)
		{
			BHUDWidget->AddToViewport();
		}
	}

	if (GamePauseWidgetClass)
	{
		GamePauseWidget = CreateWidget<UBGamePauseWidget>(this, GamePauseWidgetClass);
	}

	BHUDWidget->BindPlayerState(BPlayerState);

	SetClickMode(false);
}

void ABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ABPlayerController::OnGamePuase);
}

void ABPlayerController::OnPossess(APawn * aPawn)
{
	Super::OnPossess(aPawn);
	
	BPlayerState = Cast<ABPlayerState>(PlayerState);
	BCHECK(BPlayerState);
	BPlayerState->InitPlayerData(aPawn);
}

UBHUDWidget * ABPlayerController::GetHUDWidget() const
{
	return BHUDWidget;
}

UBGamePauseWidget * ABPlayerController::GetGamePauseWidget() const
{
	return GamePauseWidget;
}

void ABPlayerController::MonsterKill(ABEnemyBase * KilledMonster)
{
	int32 MonsterDropMoney = KilledMonster->GetCurrentStat()->GetDropMoney();

	BPlayerState->AddMoney(MonsterDropMoney);

	UKismetSystemLibrary::DrawDebugString(GetWorld(), KilledMonster->GetActorLocation(), FString::Printf(TEXT("+%d"), MonsterDropMoney), NULL, FLinearColor::Yellow, 2.0f);
	// 화면에 돈 출력.
}

void ABPlayerController::SetClickMode(bool IsClickMode)
{
	if (IsClickMode)
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
}

void ABPlayerController::OnGamePuase()
{
	if (GamePauseWidget != nullptr)
	{
		GamePauseWidget->AddToViewport(3);
	}

	BHUDWidget->SetCanNotClickButton();
	SetPause(true);

	if (BHUDWidget->IsPlayingAnimation())
	{
		BHUDWidget->PauseAllAnimation();
	}

	SetClickMode(true);
}
