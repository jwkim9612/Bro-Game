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
	Defense,
	MaxHP,
	Speed,
	Combo
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
	TArray<FName> MonsterName;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> Num;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> MaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<float> Speed;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<float> Size;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<int32> DropMoney;
};

USTRUCT()
struct BROGAME_API FBBossSpawnInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	FName BossName;
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

USTRUCT()
struct BROGAME_API FBMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	TSubclassOf<class ABMonster> Class;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float CapsuleHalfHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float CapsuleRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float MeshZLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float DefaultDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float DefaultMaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 DefaultDropMoney;
};

USTRUCT()
struct BROGAME_API FBBossInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	TSubclassOf<class ABBoss> Class;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float MaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 DropMoney;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	UTexture2D* WantedPhoto;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	UParticleSystem* HitParticle;
};
