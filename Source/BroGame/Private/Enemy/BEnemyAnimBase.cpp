// Fill out your copyright notice in the Description page of Project Settings.


#include "BEnemyAnimBase.h"
#include "BEnemyBase.h"

void UBEnemyAnimBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Monster != nullptr)
	{
		CurrentSpeed = Monster->GetVelocity().Size();
	}

	if (bIsDead)
	{
		//Stops the animation montage. If reference is NULL, it will stop ALL active montages.
		Montage_Stop(0.0f);
	}
}

void UBEnemyAnimBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Monster = Cast<ABEnemyBase>(TryGetPawnOwner());
}

void UBEnemyAnimBase::AnimNotify_HitAttack()
{
	OnHitAttack.Broadcast();
}

void UBEnemyAnimBase::SetIsDead(bool IsDead)
{
	bIsDead = IsDead;
}

void UBEnemyAnimBase::PlayAttackMontage()
{
	BCHECK(AttackMontage != nullptr);
	Montage_Play(AttackMontage);
}
