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

	CurrentWave = StartingWave;
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
			if (IsBonusWaveClear())
			{
				OnBonusWaveClear.Broadcast();
			}

			++CurrentWave;
			OnCurrentWaveChange.Broadcast();
			SetIsClear(true);
			StartTimer();
		}
		break;
	case EWaveType::Boss:
		if (CurrentWaveState == EWaveState::PLAY && IsBossDead)
		{
			if (IsBonusWaveClear())
			{
				OnBonusWaveClear.Broadcast();
			}

			++CurrentWave;
			OnCurrentWaveChange.Broadcast();
			OnIsBossDead.Broadcast();
			SetIsClear(true);
			StartTimer();
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

bool ABGameStateBase::IsBonusWaveClear() const
{
	int32 CheckWave = CurrentWave % 10;

	if (CheckWave == 3 || CheckWave == 6 || CheckWave == 0)
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

	// CurrentWave가 Text이기 때문에 Text가 9인 상태에서 타이머가 시작되면 다음이 보스이기 때문에 +1을 해줌.
	//ChangeWaveType(CurrentWave + 1);
	ChangeWaveType(CurrentWave);

	switch (CurrentWaveType)
	{
	case EWaveType::Normal:
		CurrentTimeMin = BGameModeBase->GetNormalTimeMin();
		CurrentTimeSec = BGameModeBase->GetNormalTimeSec();
		break;
	case EWaveType::Boss:
		CurrentTimeMin = BGameModeBase->GetBossTimeMin();
		CurrentTimeSec = BGameModeBase->GetBossTimeSec();
		OnReadyToBoss.Broadcast();
		break;
	}
	
	GetWorld()->GetTimerManager().SetTimer(CountDownTimerHandle, this, &ABGameStateBase::TickPerSecond, TimerDeltaSeconds, true);

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
		//++CurrentWave;
		//ChangeWaveType(CurrentWave);

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
