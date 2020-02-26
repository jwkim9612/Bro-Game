// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Actor.h"
#include "BBossSpawner.generated.h"

UCLASS()
class BROGAME_API ABBossSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABBossSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

public:
	TArray<TSubclassOf<class ABBoss>> GetBosses() const;
	

private:
	UFUNCTION()
	void Spawn();

private:
	UPROPERTY(VisibleAnywhere, Category = "Box", meta = (AllowPrivateAccess = true))
	UBoxComponent* SpawnVolume;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY()
	class UBGameInstance* BGameInstance;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TArray<TSubclassOf<class ABBoss>> BossClass;
};
