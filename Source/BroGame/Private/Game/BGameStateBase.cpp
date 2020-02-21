// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameStateBase.h"
#include "BGameModeBase.h"

ABGameStateBase::ABGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BGameModeBase = Cast<ABGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

void ABGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	StartTimer();
}

void ABGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentWaveState == EWaveState::PLAY && CurrentMonsterNum == 0)
	{
		SetIsClear(true);
		StartTimer();
	}
}

bool ABGameStateBase::IsCountDownDone() const
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

bool ABGameStateBase::IsStageClear() const
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

void ABGameStateBase::SetIsClear(bool IsClear)
{
	bIsClear = IsClear;
}

int32 ABGameStateBase::GetCurrentTimeMin() const
{
	return CurrentTimeMin;
}

int32 ABGameStateBase::GetCurrentTimeSec() const
{
	return CurrentTimeSec;
}

int32 ABGameStateBase::GetCurrentWave() const
{
	return CurrentWave;
}

void ABGameStateBase::AddMonsterNum()
{
	++CurrentMonsterNum;
}

void ABGameStateBase::SubMonsterNum()
{
	if (CurrentMonsterNum == 0)
	{
		return;
	}

	--CurrentMonsterNum;
}

void ABGameStateBase::StartTimer()
{
	CurrentWaveState = EWaveState::READY;

	// if( 보스탄이 아니면 )
	CurrentTimeMin = BGameModeBase->GetDefaultTimeMin();
	CurrentTimeSec = BGameModeBase->GetDefaultTimeSec();
	GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, this, &ABGameStateBase::TickPerSecond, TimerDeltaSeconds, true);
	// else

	OnCountDown.Broadcast();
	OnCountDownStart.Broadcast();
}

void ABGameStateBase::TickPerSecond()
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
		++CurrentWave;
		OnCountDownDone.Broadcast();
		CurrentWaveState = EWaveState::PLAY;
	}
}
