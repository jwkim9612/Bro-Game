// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BSpawnerBase.h"
#include "BMonsterSpawner.generated.h"

UCLASS()
class BROGAME_API ABMonsterSpawner : public ABSpawnerBase
{
	GENERATED_BODY()
	
public:	
	ABMonsterSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
public:
	// ĸ�� ����� 70�̸��� ���Ͱ� �� ������ �ִ�� ������ �� �ִ� ��
	const int MaxSpawnNum = 9;

private:
	virtual void Spawn() override;

	FVector GetSnailLocation(FVector CenterVec, int32 AreaIdx, float Size, int32 count);
	void SetSpawnData(int32 CurrentWave);

private:
	//UPROPERTY(VisibleAnywhere, Category = "Box", meta = (AllowPrivateAccess = true))
	//UBoxComponent* SpawnVolume;

	//UPROPERTY()
	//TSoftClassPtr<ACharacter> MonsterClassPtr;

	//UPROPERTY()
	//UClass* BMonsterClass;

	UPROPERTY()
	class ABMonster* BMonster;

	//UPROPERTY()
	//class ABGameStateBase* BGameStateBase;

	//UPROPERTY()
	//class UBGameInstance* BGameInstance;

	struct FBSpawnInfo CurrentSpawnData;
};