// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnCountDownStartDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCountDownDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCountDownDoneDelegate);
DECLARE_MULTICAST_DELEGATE(FOnReadyToBossDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBossCountDownDoneDelegate);

#include "BroGame.h"
#include "GameFramework/GameStateBase.h"
#include "BGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ABGameStateBase();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	bool IsCountDownDone() const;
	bool IsStageClear() const;
	void SetIsClear(bool IsClear);
	int32 GetCurrentTimeMin() const;
	int32 GetCurrentTimeSec() const;
	int32 GetCurrentWave() const;
	EWaveType GetCurrentWaveType() const;

	void AddMonsterNum();
	void SubMonsterNum();
	void SetIsBossDead(bool IsDead);

	// 잠시 옮겨둠 다시 private로 가는것이 좋아보임.
	void StartTimer();

private:
	void TickPerSecond();
	void ChangeWaveType(int32 Wave);

public:
	FOnCountDownStartDelegate OnCountDownStart;
	FOnCountDownDelegate OnCountDown;
	FOnCountDownDoneDelegate OnCountDownDone;
	FOnReadyToBossDelegate OnReadyToBoss;
	FOnBossCountDownDoneDelegate OnBossCountDownDone;

private:
	UPROPERTY()
	float TimerDeltaSeconds = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stage")
	bool bIsClear = true;

	UPROPERTY(VisibleAnywhere, Category = "Stage")
	int32 CurrentWave = 0;

	int32 CurrentMonsterNum = 0;

	UPROPERTY()
	class ABGameModeBase* BGameModeBase;

	int32 CurrentTimeMin;
	int32 CurrentTimeSec;

	FTimerHandle CountDownTimerHandle;

	EWaveState CurrentWaveState = EWaveState::PREINIT;
	EWaveType CurrentWaveType;

	bool IsBossDead = true;
};
