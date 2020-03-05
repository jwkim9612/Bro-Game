// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Actor.h"
#include "BSpawnerBase.generated.h"

UCLASS()
class BROGAME_API ABSpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABSpawnerBase();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	virtual void Spawn();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Box", meta = (AllowPrivateAccess = true))
	UBoxComponent* SpawnVolume;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* EnemyBase;

	UPROPERTY(VisibleAnywhere, Category = "Summon")
	UParticleSystemComponent* SummonParticle;

	UPROPERTY()
	TSoftClassPtr<class ABEnemyBase> EnemyClassPtr;

	UPROPERTY()
	UClass* BEnmeyClass;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY()
	class UBGameInstance* BGameInstance;
};
