// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "BDatas.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API UBDatas : public UObject
{
	GENERATED_BODY()
	
};

UENUM()
enum class EWaveState : uint8
{
	PREINIT,
	READY,
	PLAY
};

UENUM()
enum class EWaveType : uint8
{
	Normal,
	Boss
};

UENUM()
enum class EStat : uint8
{
	Attack,
	MaxHP,
	Speed
};

UENUM()
enum class  EBonusRarelity : uint8
{
	Normal,
	Rare,
	Unique,
	Legend
};

UENUM()
enum class  EBonusType : uint8
{
	Money,
	Attack,
	Speed,
	MaxHP,
	Combo
};

USTRUCT()
struct BROGAME_API FBSpawnInfo : public FTableRowBase
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

USTRUCT()
struct BROGAME_API FBBonusInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Bonus")
	FName BonusName;

	UPROPERTY(EditDefaultsOnly, Category = "Bonus")
	int32 BonusValue;

	UPROPERTY(EditDefaultsOnly, Category = "Bonus")
	EBonusRarelity Rarelity;

	UPROPERTY(EditDefaultsOnly, Category = "Bonus")
	EBonusType Type;
};
