
#include "BBossSpawner.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"
#include "BBoss.h"
#include "BPlayerController.h"
#include "BHUDWidget.h"

ABBossSpawner::ABBossSpawner()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume->SetBoxExtent(FVector(100.0f, 100.0f, 32.0f));
}

void ABBossSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABBossSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BGameStateBase != nullptr)
	{
		BGameStateBase->OnBossCountDownDone.AddUObject(this, &ABBossSpawner::Spawn);
	}
}

void ABBossSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABBoss* ABBossSpawner::GetCurrentBoss() const
{
	return BBoss;
}

void ABBossSpawner::InitBossData()
{
	int32 CurrentBossWave = BGameStateBase->GetCurrentWave() / 10;
	BCHECK(CurrentBossWave >= 0);

	SetBossSpawnData(CurrentBossWave);

	EnemyClassPtr = TSoftClassPtr<ABBoss>(FSoftObjectPath(CurrentBossSpawnData.BossClassPath));
	BCHECK(EnemyClassPtr != nullptr);

	BEnmeyClass = EnemyClassPtr.LoadSynchronous();
	BCHECK(BEnmeyClass != nullptr);

	BBoss = BEnmeyClass->GetDefaultObject<ABBoss>();
	BCHECK(BBoss != nullptr);
}

void ABBossSpawner::Spawn()
{
	FVector Vec = GetActorLocation();
	FRotator Rot = FRotator::ZeroRotator;

	if (GetWorld()->SpawnActor<ABBoss>(BBoss->GetClass(), Vec, Rot))
	{
		// 보스 소환
		BGameStateBase->SetIsBossDead(false);
	}
}

void ABBossSpawner::SetBossSpawnData(int32 CurrentBossWave)
{
	BCHECK(BGameInstance != nullptr);

	CurrentBossSpawnData = BGameInstance->GetBossSpawnDataWave(CurrentBossWave);
}
