
#include "BBossSpawner.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"
#include "BBoss.h"
#include "BPlayerController.h"
#include "BHUDWidget.h"

ABBossSpawner::ABBossSpawner()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	SpawnVolume->SetBoxExtent(FVector(100.0f, 100.0f, 32.0f));

}

void ABBossSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABBossSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BGameInstance = Cast<UBGameInstance>(GetGameInstance());
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	if (BGameStateBase != nullptr)
	{
		BGameStateBase->OnBossCountDownDone.AddUObject(this, &ABBossSpawner::Spawn);
	}
}

void ABBossSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<struct FBBossInfo> ABBossSpawner::GetBosses() const
{
	return Bosses;
}

void ABBossSpawner::Spawn()
{
	int32 BossIndex = (BGameStateBase->GetCurrentWave() / 10) - 1;
	BCHECK(BossIndex <= Bosses.Num() - 1);

	ABBoss* Boss = Bosses[BossIndex].BossClass->GetDefaultObject<ABBoss>();
	
	FVector Vec = GetActorLocation();
	FRotator Rot = FRotator::ZeroRotator;

	if (GetWorld()->SpawnActor<ABBoss>(Boss->GetClass(), Vec, Rot))
	{
		// 보스 소환
		BGameStateBase->SetIsBossDead(false);
	}
}
