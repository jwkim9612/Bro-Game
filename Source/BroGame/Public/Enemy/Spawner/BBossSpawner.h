// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BSpawnerBase.h"
#include "BBossSpawner.generated.h"

UCLASS()
class BROGAME_API ABBossSpawner : public ABSpawnerBase
{
	GENERATED_BODY()
	
public:	
	ABBossSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

public:
	class ABBoss* GetCurrentBoss() const;
	void InitBossData();

private:
	virtual void Spawn() override;

	void SetBossSpawnData(int32 CurrentBossWave);

private:
	UPROPERTY()
	class ABBoss* BBoss;

	UPROPERTY()
	TMap<FName, class ABBoss*> BossTable;

	struct FBBossSpawnInfo CurrentBossSpawnData;
};
