// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterSpawner.h"
#include "BMonster.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"

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
	int count = 0;

	for (auto Monster : Monsters[BGameStateBase->GetCurrentWave()-1].MonsterInfo)
	{
		ABMonster* BMonster = Monster.Key->GetDefaultObject<ABMonster>();
		float MonsterSize = BMonster->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2;

		for (int i = 0; i < Monster.Value; ++i)
		{
			// 좀 띄어서 나오게 20을 더해줌
			FVector vec = GetSnailLocation(GetActorLocation(), count / MaxSpawnNum, MonsterSize + 20);
			FRotator rot = FRotator::ZeroRotator;

			if (GetWorld()->SpawnActor<ACharacter>(Monster.Key, vec, rot))
			{
				BGameStateBase->AddMonsterNum();
			}

			++count;
		}
	}
}

FVector ABMonsterSpawner::GetSnailLocation(FVector CenterVec, int32 Idx, float Size)
{
	if (Idx == 0)
		return CenterVec;

	int32 IndexCounter = 0;
	int32 Sign = 1;
	int32 Snailcounter = 1;
	float CanSpawnDistance = Size * 3;

	while (1)
	{
		for (int32 i = 0; i < Snailcounter; ++i)
		{
			CenterVec += FVector(0.0f, CanSpawnDistance*Sign, 0.0f);

			++IndexCounter;
			if (Idx == IndexCounter)
				return CenterVec;
		}

		for (int32 j = 0; j < Snailcounter; ++j)
		{
			CenterVec += FVector(CanSpawnDistance*Sign, 0.0f, 0.0f);

			++IndexCounter;
			if (Idx == IndexCounter)
				return CenterVec;
		}

		Sign *= -1;
		Snailcounter++;
	}
}