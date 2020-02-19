// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BroGame.h"
#include "GameFramework/Character.h"
#include "BMonster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

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
	void Attack();
	void AttackCheck();
	float GetMaxHP() const;
	float GetDamage() const;
	float GetAttackRange() const;

public:
	FOnAttackEndDelegate OnAttackEnd;

private:
	void Dead();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* AnimMontage, bool Interrupted);

	UFUNCTION()
	void OnVisibleHPBarBoxBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnVisibleHPBarBoxEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float MaxHP;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "stat")
	float AttackRange;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HPWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UBoxComponent* VisibleHPBox;

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
	bool IsAttacking = false;

	FVector VisibleHPBarBoxSize = FVector(300.0f, 300.0f, 100.0f);
};
