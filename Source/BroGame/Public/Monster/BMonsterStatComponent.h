// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "Components/ActorComponent.h"
#include "BMonsterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BROGAME_API UBMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBMonsterStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent() override;

public:
	void InitMonsterData(class ABMonster* Monster);
	void SetHP(float NewHP);
	void SetHPToDamage(float Damage);
	float GetHP();
	float GetHPRatio();
	int32 GetAttack();

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = "Stat", Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY()
	class ABMonster* BMonster;
};
