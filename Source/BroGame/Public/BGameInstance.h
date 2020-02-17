// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "BGameInstance.generated.h"

/**
 * 
 */

USTRUCT()
struct FBSpawnData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBSpawnData() { }

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	//int32 Wave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FString> ClassName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<int32> Quantity;
};

UCLASS()
class BROGAME_API UBGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBGameInstance();

private:
	UPROPERTY()
	UDataTable* SpawnDataTable;

public:

	FBSpawnData* GetSpawnData(int32 Wave) const;

};
