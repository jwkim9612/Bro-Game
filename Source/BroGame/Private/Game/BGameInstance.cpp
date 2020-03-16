// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameInstance.h"
#include "BBonusManager.h"
#include "BMonster.h"

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

UDataTable * UBGameInstance::GetBonusDataTable() const
{
	return BonusDataTable;
}

TMap<FName, ABMonster*> UBGameInstance::GetMonsterTable() const
{
	return MonsterTable;
}

FVector UBGameInstance::GetSnailLocation(FVector CenterVec, int32 AreaIdx, float Size, int32 count)
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
