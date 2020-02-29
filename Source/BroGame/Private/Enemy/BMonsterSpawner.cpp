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

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	SpawnVolume->SetBoxExtent(FVector(200.0f, 200.0f, 32.0f));
}

void ABMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void ABMonsterSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BGameInstance = Cast<UBGameInstance>(GetGameInstance());
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	
	if (BGameStateBase != nullptr)
	{
		BGameStateBase->OnCountDownDone.AddUObject(this, &ABMonsterSpawner::Spawn);
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

	for (int32 MonsterIndex = 0; MonsterIndex < CurrentSpawnData->MonsterClassPath.Num(); ++MonsterIndex)
	{
		MonsterClassPointer = TSoftClassPtr<ABMonster>(FSoftObjectPath(CurrentSpawnData->MonsterClassPath[MonsterIndex]));
		BCHECK(MonsterClassPointer != nullptr);

		auto BMonsterClass = MonsterClassPointer.LoadSynchronous();
		BCHECK(BMonsterClass != nullptr);

		ABMonster* BMonster = BMonsterClass->GetDefaultObject<ABMonster>();
		BCHECK(BMonster != nullptr);

		BMonster->SetDamage(CurrentSpawnData->Damage[MonsterIndex]);
		BMonster->SetMaxHP(CurrentSpawnData->MaxHP[MonsterIndex]);
		BMonster->SetSpeed(CurrentSpawnData->Speed[MonsterIndex]);
		BMonster->SetSize(CurrentSpawnData->size[MonsterIndex]);
		BMonster->SetDropMoney(CurrentSpawnData->DropMoney[MonsterIndex]);

		float MonsterSize = BMonster->GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 2;

		for (int32 j = 0; j < CurrentSpawnData->Num[MonsterIndex]; ++j)
		{
			FVector vec = GetSnailLocation(GetActorLocation(), SpawnLocationCount / MaxSpawnNum, MonsterSize, SpawnLocationCount % MaxSpawnNum);
			FRotator rot = FRotator::ZeroRotator;

			if (GetWorld()->SpawnActor<ABMonster>(BMonster->GetClass(), vec, rot))
			{
				BGameStateBase->AddMonsterNum();
			}

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
	BCHECK(CurrentSpawnData != nullptr);
}
