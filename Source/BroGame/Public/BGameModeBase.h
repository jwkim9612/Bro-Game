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
	int32 GetDefaultTimeMin() const;
	int32 GetDefaultTimeSec() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 99))
	int32 DefaultTimeMin;
	
	UPROPERTY(EditDefaultsOnly, Category = "Timer", meta = (UIMin = 0, UIMax = 59))
	int32 DefaultTimeSec;
};
