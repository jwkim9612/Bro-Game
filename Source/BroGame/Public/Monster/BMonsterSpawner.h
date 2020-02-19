// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Actor.h"
#include "BMonsterSpawner.generated.h"

USTRUCT()
struct FBSpawnInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TMap<TSubclassOf<class ABMonster>, int32> MonsterInfo;
};

UCLASS()
class BROGAME_API ABMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void Spawn();

	FVector GetSnailLocation(FVector CenterVec, int32 Idx, float Size);

private:
	UPROPERTY(VisibleAnywhere, Category = "Box", meta = (AllowPrivateAccess = true))
	UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = "Spawn")	
	TArray<struct FBSpawnInfo> Monsters;
	
private:
	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	// 한 지점에 최대로 스폰할 수 있는 수
	const int MaxSpawnNum = 9;
};
