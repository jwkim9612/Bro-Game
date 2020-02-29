// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "BGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class BROGAME_API UBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBGameInstance();

public:
	virtual void Init() override;

public:
	struct FBSpawnInfo* GetSpawnDataByWave(int32 Wave);
	
	class UDataTable* GetBonusDataTable() const;

public:
	UPROPERTY()
	class UBBonusManager* BBonusManager;

private:
	UPROPERTY()
	class UDataTable* SpawnDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	class UDataTable* BonusDataTable;

};
