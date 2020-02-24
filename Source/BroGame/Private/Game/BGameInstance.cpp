// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameInstance.h"

UBGameInstance::UBGameInstance()
{
	FString SpawnMonsterDataPath = TEXT("DataTable'/Game/GameData/Spawner/SpawnData.SpawnData'");

	static ConstructorHelpers::FObjectFinder<UDataTable>
		SpawnMonster_DataTable(*SpawnMonsterDataPath);

	BCHECK(SpawnMonster_DataTable.Succeeded());
	SpawnDataTable = SpawnMonster_DataTable.Object;
	BCHECK(SpawnDataTable->GetRowMap().Num() > 0);

}

FBSpawnInfo * UBGameInstance::GetSpawnDataTable(int32 Wave)
{
	return SpawnDataTable->FindRow<FBSpawnInfo>(*FString::FromInt(Wave), TEXT(""));
}
