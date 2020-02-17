// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameInstance.h"
#include "Engine/DataTable.h"

UBGameInstance::UBGameInstance()
{
	FString SpawnDataPath = TEXT("DataTable'/Game/GameData/SpawnData.SpawnData'");

	static ConstructorHelpers::FObjectFinder<UDataTable>
		Spawn_DataTable(*SpawnDataPath);

	BCHECK(Spawn_DataTable.Succeeded());
	SpawnDataTable = Spawn_DataTable.Object;
	BCHECK(SpawnDataTable->GetRowMap().Num() > 0);
}

FBSpawnData * UBGameInstance::GetSpawnData(int32 Wave) const
{
	//return SpawnDataTable->FindRow<FBSpawnData>(*FString::FromInt(Wave), TEXT(""));
	return SpawnDataTable->FindRow<FBSpawnData>(*FString::FromInt(1), TEXT(""));
}
