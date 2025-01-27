// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Components/ActorComponent.h"
#include "BEnemyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROGAME_API UBEnemyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBEnemyStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

public:
	void InitMonsterData(class ABEnemyBase* Monster);

	UFUNCTION()
	void SetHP(float NewHP);

	UFUNCTION(BlueprintCallable)
	void SetHPToDamage(float Damage);

	float GetHP();
	float GetHPRatio();
	int32 GetDamage();
	int32 GetDropMoney();

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat")
	float CurrentHP;

	UPROPERTY()
	class ABEnemyBase* BMonster;
};
