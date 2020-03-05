// Fill out your copyright notice in the Description page of Project Settings.


#include "BLevelScriptActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "Engine/public/EngineUtils.h"

void ABLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	

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
		BLevelSequence[BossWave-1],		// �ε����� 0���� �����̹Ƿ� 1�� ����
		PlaybackSettings,
		BLevelSequenceActor[BossWave-1]
	);

	if (BLevelSequencePlayer != nullptr)
	{
		BLevelSequencePlayer->Play();
		OnStartCinematic.Broadcast();
		return true;
	}

	return false;
}
