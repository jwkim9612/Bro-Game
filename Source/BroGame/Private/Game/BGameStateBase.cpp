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

	switch (CurrentWaveType)
	{
	case EWaveType::Normal:
		if (CurrentWaveState == EWaveState::PLAY && CurrentMonsterNum == 0)
		{
			SetIsClear(true);
			StartTimer();
			BLOG(Warning, TEXT("Normal timer"));
		}
		break;
	case EWaveType::Boss:
		if (CurrentWaveState == EWaveState::PLAY && IsBossDead)
		{
			SetIsClear(true);
			StartTimer();
			BLOG(Warning, TEXT("Boss timer"));
		}
		break;
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
	return bIsClear ? true : false;
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

EWaveType ABGameStateBase::GetCurrentWaveType() const
{
	return CurrentWaveType;
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

void ABGameStateBase::SetIsBossDead(bool IsDead)
{
	IsBossDead = IsDead;
}

void ABGameStateBase::StartTimer()
{
	CurrentWaveState = EWaveState::READY;

	// if( ����ź�� �ƴϸ� )
	CurrentTimeMin = BGameModeBase->GetDefaultTimeMin();
	CurrentTimeSec = BGameModeBase->GetDefaultTimeSec();
	GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, this, &ABGameStateBase::TickPerSecond, TimerDeltaSeconds, true);
	// else

	OnCountDown.Broadcast();
	OnCountDownStart.Broadcast();
}

void ABGameStateBase::TickPerSecond()
{
	// 00 : 00���� �߰� �ϱ� ���� ������� if��
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
		ChangeWaveType(CurrentWave);

		if (CurrentWaveType == EWaveType::Boss)
		{
			OnBossCountDownDone.Broadcast();
		}

		OnCountDownDone.Broadcast();
		CurrentWaveState = EWaveState::PLAY;
	}
}

void ABGameStateBase::ChangeWaveType(int32 Wave)
{
	if (Wave % 10 == 0)
	{
		CurrentWaveType = EWaveType::Boss;
	}
	else
	{
		CurrentWaveType = EWaveType::Normal;
	}
}
