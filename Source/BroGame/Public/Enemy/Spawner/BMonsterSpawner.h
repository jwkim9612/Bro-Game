// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BSpawnerBase.h"
#include "BMonsterSpawner.generated.h"

UCLASS()
class BROGAME_API ABMonsterSpawner : public ABSpawnerBase
{
	GENERATED_BODY()
	
public:	
	ABMonsterSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
public:
	// 캡슐 사이즈가 70미만인 몬스터가 한 지점에 최대로 스폰할 수 있는 수
	const int MaxSpawnNum = 9;

private:
	virtual void Spawn() override;

	FVector GetSnailLocation(FVector CenterVec, int32 AreaIdx, float Size, int32 count);
	void SetSpawnData(int32 CurrentWave);

private:
	UPROPERTY()
	class ABMonster* BMonster;

	UPROPERTY()
	TMap<FName, class ABMonster*> MonsterTable;

	struct FBSpawnInfo CurrentSpawnData;
};
