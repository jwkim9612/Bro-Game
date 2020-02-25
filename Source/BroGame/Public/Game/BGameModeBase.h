// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



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

public:
	int32 GetNormalTimeMin() const;
	int32 GetNormalTimeSec() const;
	int32 GetBossTimeMin() const;
	int32 GetBossTimeSec() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 99))
	int32 NormalTimeMin;
	
	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 59))
	int32 NormalTimeSec;

	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 99))
	int32 BossTimeMin;

	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 59))
	int32 BossTimeSec;
};
