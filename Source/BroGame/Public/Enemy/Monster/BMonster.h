// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "BEnemyBase.h"
#include "BMonster.generated.h"

UCLASS()
class BROGAME_API ABMonster : public ABEnemyBase
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
	virtual void Attack() override;
	virtual void SetSize(float NewSize);
	void SetDefaultStat(struct FBMonsterInfo BMonsterInfo);

private:
	void virtual Dead() override;

	UFUNCTION()
	void OnVisibleHPBarBoxBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnVisibleHPBarBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HPWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UBoxComponent* VisibleHPBox;

	UPROPERTY()
	class UBMonsterAnimInstance* BMonsterAnimInstance;

	struct FBMonsterInfo MonsterData;

	FTimerHandle DeadTimerHandle;
	float DeadTimer = 3.0f;

	FVector VisibleHPBarBoxSize = FVector(300.0f, 300.0f, 100.0f);

	float DefaultCapsuleHalfHeight;
	float DefaultCapsuleRadius;
	float DefaultMeshZLocation;
};
