// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_MULTICAST_DELEGATE(FOnCountDownStartDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCountDownDelegate);
DECLARE_MULTICAST_DELEGATE(FOnCountDownDoneDelegate);

#include "BroGame.h"
#include "GameFramework/GameModeBase.h"
#include "BGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void StartPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	int32 GetCurrentTimeMin() const;
	int32 GetCurrentTimeSec() const;
	bool IsCountDownDone() const;
	bool IsStageClear() const;
	
	void SetIsClear(bool IsClear);

	// 잠시 옮겨둠 다시 private로 가는것이 좋아보임.
	void StartTimer();

private:
	void MinusSeconds();

public:
	FOnCountDownStartDelegate OnCountDownStart;
	FOnCountDownDelegate OnCountDown;
	FOnCountDownDoneDelegate OnCountDownDone;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 99))
	int32 DefaultTimeMin;
	
	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 59))
	int32 DefaultTimeSec;

	int32 CurrentTimeMin;
	int32 CurrentTimeSec;

	FTimerHandle CountDownTimerHandle;

	UPROPERTY()
	float TimerDeltaSeconds;

	UPROPERTY(EditAnywhere, Category = "Stage")
	bool bIsClear = true;
};
