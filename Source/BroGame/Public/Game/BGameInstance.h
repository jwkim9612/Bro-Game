// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "BGameInstance.generated.h"

USTRUCT()
struct FBSpawnInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<FString> MonsterClassPath;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> Num;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> MaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<float> Speed;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<float> size;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> DropMoney;
};

/**
 * 
 */

UCLASS()
class BROGAME_API UBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBGameInstance();

	FBSpawnInfo* GetSpawnDataTable(int32 Wave);

private:
	UPROPERTY()
	class UDataTable* SpawnDataTable;

};
