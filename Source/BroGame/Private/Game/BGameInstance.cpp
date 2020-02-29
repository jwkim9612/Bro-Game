// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameInstance.h"
#include "BBonusManager.h"

UBGameInstance::UBGameInstance()
{
	FString SpawnMonsterDataPath = TEXT("DataTable'/Game/GameData/Spawner/SpawnData.SpawnData'");

	static ConstructorHelpers::FObjectFinder<UDataTable>
		SpawnMonster_DataTable(*SpawnMonsterDataPath);

	BCHECK(SpawnMonster_DataTable.Succeeded());
	SpawnDataTable = SpawnMonster_DataTable.Object;
	BCHECK(SpawnDataTable->GetRowMap().Num() > 0);
}

void UBGameInstance::Init()
{
	Super::Init();

	BBonusManager = NewObject<UBBonusManager>(this);
	BBonusManager->Init();
}

FBSpawnInfo * UBGameInstance::GetSpawnDataByWave(int32 Wave)
{
	return SpawnDataTable->FindRow<FBSpawnInfo>(*FString::FromInt(Wave), TEXT(""));
}

UDataTable * UBGameInstance::GetBonusDataTable() const
{
	return BonusDataTable;
}
