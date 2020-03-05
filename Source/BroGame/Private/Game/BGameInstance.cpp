// Fill out your copyright notice in the Description page of Project Settings.


#include "BGameInstance.h"
#include "BBonusManager.h"

UBGameInstance::UBGameInstance()
{

}

void UBGameInstance::Init()
{
	Super::Init();

	BBonusManager = NewObject<UBBonusManager>(this);
	BBonusManager->Init();
}

FBSpawnInfo UBGameInstance::GetSpawnDataByWave(int32 Wave)
{
	return *SpawnDataTable->FindRow<FBSpawnInfo>(*FString::FromInt(Wave), TEXT(""));
}

FBBossSpawnInfo UBGameInstance::GetBossSpawnDataWave(int32 Wave)
{
	return *BossSpawnDataTable->FindRow<FBBossSpawnInfo>(*FString::FromInt(Wave), TEXT(""));
}

UDataTable * UBGameInstance::GetBonusDataTable() const
{
	return BonusDataTable;
}
