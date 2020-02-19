// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Character.h"
#include "BMonster.generated.h"

UCLASS()
class BROGAME_API ABMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ABMonster();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	float GetMaxHP() const;
	float GetAttack() const;

private:
	void Dead();

private:
	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float MaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float Attack;

	UPROPERTY()
	class ABAIController* BAIController;

	UPROPERTY()
	class UBMonsterAnimInstance* BMonsterAnimInstance;

	UPROPERTY()
	class ABGameStateBase* BGameStateBase;

	UPROPERTY(VisibleAnywhere, Category = "stat")
	class UBMonsterStatComponent* CurrentStat;

	FTimerHandle DeadTimerhandle;
	float DeadTimer = 3.0f;
	bool bIsDead = false;


};
