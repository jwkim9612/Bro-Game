// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameModeBase.h"
#include "BSaveGame.h"
#include "BPlayer.h"
#include "Blueprint/UserWidget.h"

void ABGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BLOG(Warning, TEXT("PostInitializeComponents"));

	UBSaveGame* BSaveGame = Cast<UBSaveGame>(UGameplayStatics::CreateSaveGameObject(UBSaveGame::StaticClass()));
	if (BSaveGame != nullptr)
	{
		BSaveGame->SaveSlotName = TEXT("Player0");
		BSaveGame->SaveIndex = 0;

		BSaveGame = Cast<UBSaveGame>(UGameplayStatics::LoadGameFromSlot(BSaveGame->SaveSlotName, BSaveGame->SaveIndex));
	}
	
	DefaultPawnClass = BSaveGame->BPlayerClass;

	TimerDeltaSeconds = 1.0f;

	StartTimer();
}

void ABGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	BLOG(Warning, TEXT("Post Login"));
}

void ABGameModeBase::StartPlay()
{
	Super::StartPlay();

	BLOG(Warning, TEXT("Start Play"));
}

void ABGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

int32 ABGameModeBase::GetCurrentTimeMin() const
{
	return CurrentTimeMin;
}

int32 ABGameModeBase::GetCurrentTimeSec() const
{
	return CurrentTimeSec;
}

bool ABGameModeBase::IsCountDownDone() const
{
	if (CurrentTimeMin == 0 && CurrentTimeSec == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ABGameModeBase::IsStageClear() const
{
	if (bIsClear)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ABGameModeBase::SetIsClear(bool IsClear)
{
	bIsClear = IsClear;
}

void ABGameModeBase::StartTimer()
{
	// if( 보스탄이 아니면 )
		CurrentTimeMin = DefaultTimeMin;
		CurrentTimeSec = DefaultTimeSec;
		GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, this, &ABGameModeBase::MinusSeconds, TimerDeltaSeconds, true);
	// else
		
	OnCountDown.Broadcast();
	OnCountDownStart.Broadcast();
}

void ABGameModeBase::MinusSeconds()
{
	// 00 : 00까지 뜨게 하기 위해 만들어준 if문
	if (CurrentTimeMin == 0 && CurrentTimeSec <= 0)
	{
		CurrentTimeSec -= 1;
	}
	else if (CurrentTimeSec <= 0)
	{
		CurrentTimeMin -= 1;
		CurrentTimeSec = 59;
	}
	else
	{
		CurrentTimeSec -= 1;
	}

	OnCountDown.Broadcast();

	if (IsCountDownDone())
	{
		bIsClear = false;
		GetWorld()->GetTimerManager().ClearTimer(CountDownTimerHandle);
		OnCountDownDone.Broadcast();
	}
}
