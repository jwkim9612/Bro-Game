// Fill out your copyright notice in the Description page of Project Settings.


#include "BLevelScriptActor.h"
#include "BGameInstance.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "Engine/public/EngineUtils.h"

void ABLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	BCHECK(BGameInstance != nullptr);

	BGameInstance->SetLevelScriptActor();
}

ULevelSequencePlayer * ABLevelScriptActor::GetLevelSequencePlayer() const
{
	return BLevelSequencePlayer;
}

bool ABLevelScriptActor::PlayBossCinematic(int32 BossWave)
{
	if (BLevelSequence.Num() < BossWave || BLevelSequenceActor.Num() < BossWave)
	{
		return false;
	}

	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	BLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(),
		BLevelSequence[BossWave-1],		// ÀÎµ¦½º´Â 0ºÎÅÍ ½ÃÀÛÀÌ¹Ç·Î 1À» »©ÁÜ
		PlaybackSettings,
		BLevelSequenceActor[BossWave-1]
	);

	if (BLevelSequencePlayer != nullptr)
	{
		SequenceTimer = BLevelSequencePlayer->GetDuration().AsSeconds() + 0.5f;

		BLevelSequencePlayer->Play();
		GetWorld()->GetTimerManager().SetTimer(SequenceTimerHandle, this, &ABLevelScriptActor::OnCinemaEnded, SequenceTimer, false);
		return true;
	}

	return false;
}

void ABLevelScriptActor::OnCinemaEnded()
{
	OnEndCinematic.Broadcast();
}
