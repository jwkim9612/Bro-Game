// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterSpawner.h"
#include "BMonster.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"
#include "BDatas.h"
#include "UObject/SoftObjectPtr.h"

ABMonsterSpawner::ABMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume->SetBoxExtent(FVector(200.0f, 200.0f, 32.0f));
}

void ABMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void ABMonsterSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BGameStateBase != nullptr)
	{
		BGameStateBase->OnCountDownDone.AddUObject(this, &ABMonsterSpawner::Spawn);
		BGameStateBase->OnCountDownDone.AddLambda([this]() -> void {
			SummonParticle->SetVisibility(false);
		});

		BGameStateBase->OnReadyToMonster.AddLambda([this]() -> void {
			SummonParticle->SetVisibility(true);
		});
	}
}

void ABMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABMonsterSpawner::Spawn()
{
	int32 SpawnLocationCount = 0;

	int32 CurrentWave = BGameStateBase->GetCurrentWave();
	// SpawnData�� �ε����� 0���� �����̹Ƿ� 1�� ���ش�.
	SetSpawnData(CurrentWave);

	for (int32 MonsterIndex = 0; MonsterIndex < CurrentSpawnData.MonsterName.Num(); ++MonsterIndex)
	{
		auto MonsterTable = BGameInstance->GetMonsterTable();

		BMonster = *MonsterTable.Find(CurrentSpawnData.MonsterName[MonsterIndex]);
		
		BCHECK(nullptr != BMonster);
		BMonster->SetDamage(CurrentSpawnData.Damage[MonsterIndex]);
		BMonster->SetMaxHP(CurrentSpawnData.MaxHP[MonsterIndex]);
		BMonster->SetSpeed(CurrentSpawnData.Speed[MonsterIndex]);
		BMonster->SetSize(CurrentSpawnData.Size[MonsterIndex]);
		BMonster->SetDropMoney(CurrentSpawnData.DropMoney[MonsterIndex]);

		//EnemyClassPtr = TSoftClassPtr<ABMonster>(FSoftObjectPath(CurrentSpawnData.MonsterClassPath[MonsterIndex]));
		//BCHECK(EnemyClassPtr != nullptr);

		//BEnmeyClass = EnemyClassPtr.LoadSynchronous();
		//BCHECK(BEnmeyClass != nullptr);

		//BMonster = BEnmeyClass->GetDefaultObject<ABMonster>();
		//BCHECK(BMonster != nullptr);

		float MonsterSize = BMonster->GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 2;

		for (int32 j = 0; j < CurrentSpawnData.Num[MonsterIndex]; ++j)
		{
			FVector vec = GetSnailLocation(GetActorLocation(), SpawnLocationCount / MaxSpawnNum, MonsterSize, SpawnLocationCount % MaxSpawnNum);
			FRotator rot = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<ABMonster>(BMonster->GetClass(), vec, rot);

			++SpawnLocationCount;
		}
	}
}

FVector ABMonsterSpawner::GetSnailLocation(FVector CenterVec, int32 AreaIdx, float Size, int32 count)
{
	// ĸ�� ����� 70�̻��̸� ���ļ� ������ �ȵ�.
	if (AreaIdx == 0 && Size < 70.0f)
	{
		return CenterVec;
	}

	int32 IndexCounter = 0;
	int32 Sign = 1;
	int32 Snailcounter = 1;
	float CanSpawnDistance = Size * 3 + 30;

	// ���� �����ġ ���ϱ�
	while (AreaIdx != IndexCounter)
	{
		for (int32 i = 0; i < Snailcounter; ++i)
		{
			CenterVec += FVector(0.0f, CanSpawnDistance*Sign, 0.0f);

			++IndexCounter;
			if (AreaIdx == IndexCounter)
				goto Exit;
				//break;
				//return CenterVec;
		}

		for (int32 j = 0; j < Snailcounter; ++j)
		{
			CenterVec += FVector(CanSpawnDistance*Sign, 0.0f, 0.0f);

			++IndexCounter;
			if (AreaIdx == IndexCounter)
				goto Exit;
				//break;
				//return CenterVec;
		}

		Sign *= -1;
		Snailcounter++;
	}

// goto �ᵵ�Ǵ��� �����.
Exit:

	// ����� 70�̸��̸� ����
	if (Size < 70.0f)
	{
		return CenterVec;
	}

	IndexCounter = 0;
	Sign = 1;
	Snailcounter = 1;

	// �����ȿ����� ��ġ ���ϱ�
	while (IndexCounter != count)
	{
		for (int32 i = 0; i < Snailcounter; ++i)
		{
			CenterVec += FVector(0.0f, Size*Sign, 0.0f);

			++IndexCounter;
			if (count == IndexCounter)
				return CenterVec;
		}

		for (int32 j = 0; j < Snailcounter; ++j)
		{
			CenterVec += FVector(Size*Sign, 0.0f, 0.0f);

			++IndexCounter;
			if (count == IndexCounter)
				return CenterVec;
		}

		Sign *= -1;
		Snailcounter++;
	}

	return CenterVec;
}

void ABMonsterSpawner::SetSpawnData(int32 CurrentWave)
{
	BCHECK(BGameInstance != nullptr);

	CurrentSpawnData = BGameInstance->GetSpawnDataByWave(CurrentWave);
}
