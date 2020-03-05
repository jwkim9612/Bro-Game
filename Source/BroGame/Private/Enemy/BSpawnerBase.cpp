// Fill out your copyright notice in the Description page of Project Settings.


#include "BSpawnerBase.h"
#include "BGameStateBase.h"
#include "BGameInstance.h"

ABSpawnerBase::ABSpawnerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	EnemyBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyBase"));
	SummonParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SummonParticle"));
	RootComponent = SpawnVolume;
	EnemyBase->SetupAttachment(RootComponent);
	SummonParticle->SetupAttachment(RootComponent);
	SummonParticle->SetVisibility(false);
}

void ABSpawnerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABSpawnerBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BGameInstance = Cast<UBGameInstance>(GetGameInstance());
	BGameStateBase = Cast<ABGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
}

void ABSpawnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABSpawnerBase::Spawn()
{

}
