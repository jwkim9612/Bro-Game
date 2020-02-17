// Fill out your copyright notice in the Description page of Project Settings.


#include "BMonsterSpawner.h"
#include "BMonster.h"
#include "BGameStateBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABMonsterSpawner::ABMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(RootComponent);

	SpawnVolume->SetBoxExtent(FVector(100.0f, 100.0f, 32.0f));
}

// Called when the game starts or when spawned
void ABMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	//Spawn();
}

void ABMonsterSpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABGameStateBase* BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
	
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
	FVector vec = UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->Bounds.Origin, SpawnVolume->GetScaledBoxExtent());
	FRotator rot = FRotator::ZeroRotator;

	GetWorld()->SpawnActor<ACharacter>(MonsterToSpawn, vec, rot);
}

