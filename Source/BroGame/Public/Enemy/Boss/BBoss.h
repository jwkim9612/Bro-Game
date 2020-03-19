// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BEnemyBase.h"
#include "BBoss.generated.h"

/**
 * 
 */
UCLASS()
class BROGAME_API ABBoss : public ABEnemyBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	FName GetBossName() const;
	class UTexture2D* GetWantedPhoto() const;
	class UBBossAnimInstance* GetAnimInstance() const;
	void SetWantedPhoto(class UTexture2D* NewWantedPhoto);
	void SetHitParticle(class UParticleSystem* NewHitParticle);
	void SetStat(struct FBBossInfo BossInfo);

	void virtual Attack() override;

private:
	void virtual Dead() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "stat")
	FName BossName;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	class UTexture2D* WantedPhoto;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	UParticleSystem* HitParticle;

	UPROPERTY()
	class UBBossAnimInstance* BBossAnimInstance;

	FTimerHandle DeadTimerhandle;
	float DeadTimer = 3.0f;
};
