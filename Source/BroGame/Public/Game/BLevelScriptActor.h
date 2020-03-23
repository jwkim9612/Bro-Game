// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Engine/LevelScriptActor.h"
#include "BLevelScriptActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStartCinematicDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndCinematicDelegate);

/**
 * 
 */
UCLASS()
class BROGAME_API ABLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

public:
	class ULevelSequencePlayer* GetLevelSequencePlayer() const;

	bool PlayBossCinematic(int32 BossIndex);

public:
	FOnStartCinematicDelegate OnStartCinematic;
	FOnEndCinematicDelegate OnEndCinematic;

public:
	UPROPERTY()
	class ULevelSequencePlayer* BLevelSequencePlayer;

	UPROPERTY(EditAnywhere, Category = "Actor")
	TArray<class ULevelSequence*> BLevelSequence;

	UPROPERTY(EditAnywhere, Category = "Actor")
	TArray<class ALevelSequenceActor*> BLevelSequenceActor;

private:
	void OnCinemaEnded();

private:
	UPROPERTY()
	class UBGameInstance* BGameInstance;

	FTimerHandle SequenceTimerHandle;
	float SequenceTimer;
	
};
