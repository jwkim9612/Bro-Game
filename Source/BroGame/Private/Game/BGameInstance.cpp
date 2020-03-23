// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameInstance.h"
#include "BBonusManager.h"
#include "BMonster.h"
#include "BBoss.h"
#include "BLevelScriptActor.h"

UBGameInstance::UBGameInstance()
{

}

void UBGameInstance::Init()
{
	Super::Init();

	BBonusManager = NewObject<UBBonusManager>(this);
	BBonusManager->Init();
}

FBSpawnInfo UBGameInstance::GetSpawnDataByWave(int32 Wave)
{
	return *SpawnDataTable->FindRow<FBSpawnInfo>(*FString::FromInt(Wave), TEXT(""));
}

FBBossSpawnInfo UBGameInstance::GetBossSpawnDataWave(int32 Wave)
{
	return *BossSpawnDataTable->FindRow<FBBossSpawnInfo>(*FString::FromInt(Wave), TEXT(""));
}

FBMonsterInfo UBGameInstance::GetMonsterData(FName MonsterName)
{
	return *MonsterDataTable->FindRow<FBMonsterInfo>(MonsterName, TEXT(""));
}

FBBossInfo UBGameInstance::GetBossData(FName BossName)
{
	return *BossDataTable->FindRow<FBBossInfo>(BossName, TEXT(""));
}

UDataTable * UBGameInstance::GetBonusDataTable() const
{
	return BonusDataTable;
}

ABLevelScriptActor * UBGameInstance::GetCurrentLevelScriptActor() const
{
	return CurrentLevelScriptActor;
}

TMap<FName, ABMonster*> UBGameInstance::GetMonsterTable() const
{
	return MonsterTable;
}

TMap<FName, class ABBoss*> UBGameInstance::GetBossTable() const
{
	return BossTable;
}

FVector UBGameInstance::GetSnailLocation(FVector CenterVec, int32 AreaIdx, float Size, int32 count)
{
	// 캡슐 사이즈가 70이상이면 겹쳐서 스폰이 안됨.
	if (AreaIdx == 0 && Size < 70.0f)
	{
		return CenterVec;
	}

	int32 IndexCounter = 0;
	int32 Sign = 1;
	int32 Snailcounter = 1;
	float CanSpawnDistance = Size * 3 + 30;

	// 구역 가운데위치 구하기
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

	// goto 써도되는지 물어보기.
Exit:

	// 사이즈가 70미만이면 리턴
	if (Size < 70.0f)
	{
		return CenterVec;
	}

	IndexCounter = 0;
	Sign = 1;
	Snailcounter = 1;

	// 구역안에서의 위치 구하기
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

void UBGameInstance::LoadMonster()
{
	BCHECK(nullptr != MonsterDataTable);
		
	TArray<FName> Names = MonsterDataTable->GetRowNames();
	for (const auto& Name : Names)
	{
		FBMonsterInfo* Data = MonsterDataTable->FindRow<FBMonsterInfo>(Name, TEXT(""));
		if (Data->Class != nullptr)
		{
			auto* Monster = Data->Class->GetDefaultObject<ABMonster>();
			Monster->SetDefaultStat(*Data);
			MonsterTable.Add(Name, Monster);
		}
	}
}

void UBGameInstance::LoadBoss()
{
	BCHECK(nullptr != BossDataTable);

	TArray<FName> Names = BossDataTable->GetRowNames();
	for (const auto& Name : Names)
	{
		FBBossInfo* Data = BossDataTable->FindRow<FBBossInfo>(Name, TEXT(""));
		if (Data->Class != nullptr)
		{
			auto* Boss = Data->Class->GetDefaultObject<ABBoss>();
			Boss->SetStat(*Data);
			BossTable.Add(Name, Boss);
		}
	}
}

void UBGameInstance::SetLevelScriptActor()
{
	CurrentLevelScriptActor = Cast<ABLevelScriptActor>(GetWorld()->GetLevelScriptActor());
}
