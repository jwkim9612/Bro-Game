// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnCountDownStartDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCountDownDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCountDownDoneDelegate);

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
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	bool IsCountDownDone() const;
	bool IsStageClear() const;
	void SetIsClear(bool IsClear);
	int32 GetCurrentTimeMin() const;
	int32 GetCurrentTimeSec() const;

	// 잠시 옮겨둠 다시 private로 가는것이 좋아보임.
	void StartTimer();

private:
	void TickPerSecond();

public:
	FOnCountDownStartDelegate OnCountDownStart;
	FOnCountDownDelegate OnCountDown;
	FOnCountDownDoneDelegate OnCountDownDone;

private:
	UPROPERTY()
	float TimerDeltaSeconds = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stage")
	bool bIsClear = true;

	UPROPERTY()
	int32 CurrentWave;

	int32 CurrentTimeMin;
	int32 CurrentTimeSec;

	FTimerHandle CountDownTimerHandle;

	class ABGameModeBase* BGameModeBase = nullptr;
};
