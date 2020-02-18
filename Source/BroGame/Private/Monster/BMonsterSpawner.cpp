// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterSpawner.h"
#include "BMonster.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"

// Sets default values
ABMonsterSpawner::ABMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	SpawnVolume->SetBoxExtent(FVector(200.0f, 200.0f, 32.0f));
}

// Called when the game starts or when spawned
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

// Called every frame
void ABMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABMonsterSpawner::Spawn()
{
	const int MaxSpawnNum = 9;

	int count = 1;

	for (auto Monster : Monsters[BGameStateBase->GetCurrentWave()-1].MonsterInfo)
	{
		ABMonster* SpawnMonster = Monster.Key->GetDefaultObject<ABMonster>();
		float MonsterSize = SpawnMonster->GetCapsuleComponent()->GetScaledCapsuleRadius() * 2;

		for (int i = 0; i < Monster.Value; ++i)
		{
			FVector vec = GetSnailVector(GetActorLocation(), count / MaxSpawnNum, MonsterSize + 20);
			FRotator rot = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<ACharacter>(Monster.Key, vec, rot);

			++count;
		}
	}
}

FVector ABMonsterSpawner::GetSnailVector(FVector CenterVec, int32 Idx, float Size)
{
	if (Idx == 0)
		return CenterVec;

	int32 IndexCounter = 0;
	int32 Sign = 1;
	int32 Snailcounter = 1;

	//ÈÄ¿¡ ¹Ù²Ü°Í
	Size = Size * 3;

	while (1)
	{
		for (int32 i = 0; i < Snailcounter; ++i)
		{
			CenterVec += FVector(0.0f, Size*Sign, 0.0f);

			++IndexCounter;
			if (Idx == IndexCounter)
				return CenterVec;
		}

		for (int32 j = 0; j < Snailcounter; ++j)
		{
			CenterVec += FVector(Size*Sign, 0.0f, 0.0f);

			++IndexCounter;
			if (Idx == IndexCounter)
				return CenterVec;
		}

		Sign *= -1;
		Snailcounter++;
	}
}