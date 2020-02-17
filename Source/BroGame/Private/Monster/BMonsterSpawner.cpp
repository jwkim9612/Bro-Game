// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterSpawner.h"
#include "BMonster.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABMonsterSpawner::ABMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootComponent);

	SpawnVolume->SetBoxExtent(FVector(200.0f, 200.0f, 32.0f));
}

// Called when the game starts or when spawned
void ABMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//UBGameInstance* BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//if (BGameInstance != nullptr)
	//{
	//	CurrentSpawnData = BGameInstance->GetSpawnData(BGameStateBase->GetCurrentWave() + 1);
	//}

	
	//Spawn();
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
	//UBGameInstance* BGameInstance = Cast<UBGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	for (auto Monster : Monsters[BGameStateBase->GetCurrentWave()-1].MonsterInfo)
	{
		for (int i = 0; i < Monster.Value; ++i)
		{
			FVector vec = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->Bounds.Origin, SpawnVolume->GetScaledBoxExtent());
			FRotator rot = FRotator::ZeroRotator;

			GetWorld()->SpawnActor<ACharacter>(Monster.Key, vec, rot);
		}
	}

	//CurrentSpawnData = BGameInstance->GetSpawnData(BGameStateBase->GetCurrentWave()+1);

	//for (int i = 0; i < CurrentSpawnData->ClassName.Num(); ++i)
	//{
	//	//ConstructorHelpers::FClassFinder<ACharacter> MyMonster((*CurrentSpawnData->ClassName[i]));
	//	ConstructorHelpers::FClassFinder<ACharacter> MyMonster(TEXT("Blueprint'/Game/Character/Monster/BMonster_BP.BMonster_BP_C'"));

	//	if (MyMonster.Succeeded())
	//	{
	//		SpawnInfo.MonsterToSpawn = MyMonster.Class;
	//	}

	//	for (int j = 0; j < CurrentSpawnData->Quantity[j]; ++j)
	//	{
	//		FVector vec = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->Bounds.Origin, SpawnVolume->GetScaledBoxExtent());
	//		FRotator rot = FRotator::ZeroRotator;

	//		GetWorld()->SpawnActor<ACharacter>(SpawnInfo.MonsterToSpawn, vec, rot);
	//	}
	//}

	//for (auto Monster : SpawnInfo)
	//{
	//	for (int i = 0; i < Monster.Quantity; ++i)
	//	{
	//		FVector vec = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->Bounds.Origin, SpawnVolume->GetScaledBoxExtent());
	//		FRotator rot = FRotator::ZeroRotator;

	//		GetWorld()->SpawnActor<ACharacter>(Monster.MonsterToSpawn, vec, rot);
	//	}
	//}

	//for (int i = 0; i < Quantity; ++i)
	//{
	//	FVector vec = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->Bounds.Origin, SpawnVolume->GetScaledBoxExtent());
	//	FRotator rot = FRotator::ZeroRotator;

	//	GetWorld()->SpawnActor<ACharacter>(MonsterToSpawn, vec, rot);
	//}
}
