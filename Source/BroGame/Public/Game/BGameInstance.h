// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/StreamableManager.h"
#include "BGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class BROGAME_API UBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBGameInstance();

public:
	virtual void Init() override;

public:
	struct FBSpawnInfo GetSpawnDataByWave(int32 Wave);
	struct FBBossSpawnInfo GetBossSpawnDataWave(int32 Wave);
	struct FBMonsterInfo GetMonsterData(FName MonsterName);
	class UDataTable* GetBonusDataTable() const;

	TMap<FName, class ABMonster*> GetMonsterTable() const;

	FVector GetSnailLocation(FVector CenterVec, int32 AreaIdx, float Size, int32 count);

public:
	void LoadMonster();

public:
	FStreamableManager AssetLoader;

public:
	UPROPERTY()
	class UBBonusManager* BBonusManager;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* SpawnDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* BossSpawnDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* MonsterDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* BonusDataTable;

private:
	UPROPERTY()
	TMap<FName, class ABMonster*> MonsterTable;
};
